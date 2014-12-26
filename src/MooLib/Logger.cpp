#include "pch.h"
#include "Logger.h"
#include "Threading.h"


namespace ml {
namespace log {
namespace {
	std::vector<BaseWriter*> writers_;
	std::mutex mut_;

	std::vector<BaseWriter*>::iterator find_writer(const BaseWriter* ptr)
	{
		return std::find(writers_.begin(), writers_.end(), ptr);
	}

	ReturnCode remove_writer(const BaseWriter* ptr)
	{
		std::lock_guard<std::mutex> lock(mut_);

		auto pos = find_writer(ptr);
		if (pos != writers_.end()) {
			writers_.erase(pos);
			return ReturnCode::Success;
		}

		ML_ASSERT(false, "Writer not found.")(writers_.size(), (uint32_t)ptr);

		return ReturnCode::NotFound;
	}

	void write(const char* Entry)
	{
		std::lock_guard<std::mutex> lock(mut_);
		for (auto writer : writers_) {
			writer->Write(Entry, std::chrono::system_clock::now());
		}
	}
} // namespace



const char* GetRetCodeString(ReturnCode Code)
{
	switch (Code)
	{
	case ReturnCode::Success:
		return "Success";
	case ReturnCode::Failure:
		return "Failure";
	case ReturnCode::Fatal:
		return "Fatal";
	case ReturnCode::NotFound:
		return "Not Found";
	case ReturnCode::AlreadyExists:
		return "Already Exists";
	case ReturnCode::InvalidParameter:
		return "Invalid Parameter";
	default:
		return "";
	}
}


ReturnCode AddWriter(BaseWriter* Writer_Object)
{
	ML_ASSERT(find_writer(Writer_Object) == writers_.end(), "Writer already added.")();
	if (find_writer(Writer_Object) != writers_.end()) {
		return ReturnCode::AlreadyExists;
	}

	writers_.push_back(Writer_Object);
	return ReturnCode::Success;
}


void ClearWriters()
{
	std::lock_guard<std::mutex> lock(mut_);

	for (BaseWriter* writer : writers_) 
	{
		writer->Close();
	}

	writers_.clear();
}


void Write(const char* Entry_Format, ...)
{
	va_list args;
	va_start(args, Entry_Format);

	std::array<char, 8192> buf;
	uint32_t len = 0;

	// @TODO: use portable vsprintf_s
	auto ret = vsprintf_s(buf.data() + len, buf.size() - len, Entry_Format, args);
	ML_ASSERT(ret != -1, "vsprintf_s failed.")(buf.data() + len, buf.size() - len, len, Entry_Format);

	if (ret == -1) {
		strcpy(buf.data(), "Invalid assert string format >> ");
		len += 32;
		strcpy(buf.data() + len, Entry_Format);
	}

	write(buf.data());

	va_end(args);
}


void Write(const SourceInfo& Source_Info, const char* Entry_Format, ...)
{
	va_list args;
	va_start(args, Entry_Format);

	std::array<char, 8192> buf;

	int len = Source_Info.Format(buf.data());

	strcpy(buf.data() + len, " >> ");
	len += 4;

	// @TODO: use portable vsprintf_s
	auto ret = vsprintf_s(buf.data() + len, buf.size() - len, Entry_Format, args);
	ML_ASSERT(ret != -1, "vsprintf_s failed.")(buf.data() + len, buf.size() - len, len, Entry_Format);

	if (ret == -1) {
		strcpy(buf.data() + len, "Invalid assert string format >> ");
		len += 32;
		strcpy(buf.data() + len, Entry_Format);
	}

	write(buf.data());

	va_end(args);
}



// ---------------------------------------------------------------------------------------------------------------------
// class BaseWriter implementation
// ---------------------------------------------------------------------------------------------------------------------
BaseWriter::BaseWriter()
{
}


BaseWriter::~BaseWriter()
{
	remove_writer(this);
}



// ---------------------------------------------------------------------------------------------------------------------
// class BasicFileWriter implementation
// ---------------------------------------------------------------------------------------------------------------------
BasicFileWriter::BasicFileWriter()
	: file_(INVALID_HANDLE_VALUE)
{
}


BasicFileWriter::~BasicFileWriter()
{
	if (file_ != INVALID_HANDLE_VALUE) {
		CloseHandle(file_);
	}
}


ReturnCode BasicFileWriter::Init(const std::string& File_Directory, const std::string& File_Name, const std::string& File_Ext, 
						   bool Format_Date/*=true*/, const std::string& Endline_Sequence/*="\r\n"*/, uint32_t Max_Entry_Length/*=4096*/)
{
	ML_ASSERT(this->file_ == INVALID_HANDLE_VALUE, "Logging file handle already created.")(File_Name.c_str());
	ML_ASSERT(Max_Entry_Length <= 8192, "Input max log entry length is too long")(Max_Entry_Length);
	ML_ASSERT(!File_Directory.empty(), "Logging file directory empty.")();
	ML_ASSERT(!File_Name.empty(), "Logging file name empty.")();
	ML_ASSERT(Endline_Sequence.length() < 16, "Endline sequence too long empty.")(Endline_Sequence.c_str());

	// 2 = dot & terminating character
	std::size_t full_length = File_Directory.length() + File_Name.length() + File_Ext.length() + 2;

	if (full_length > MAX_PATH) {
		ML_ASSERT(full_length <= MAX_PATH, "Logging file path could not be created as path is too long.")
		(full_length, File_Directory.length(), File_Name.length(), File_Ext.length());
		return ReturnCode::InvalidParameter;
	}

	int createdir_ret = SHCreateDirectoryEx(nullptr, File_Directory.c_str(), nullptr);
	if (createdir_ret != ERROR_SUCCESS && 
	createdir_ret != ERROR_FILE_EXISTS && 
	createdir_ret != ERROR_ALREADY_EXISTS) {
		ML_ASSERT(false, "SHCreateDirectoryEx(nullptr, \"%s\", nullptr) failed.", File_Directory.c_str())(createdir_ret);
		return ReturnCode::Failure;
	}


	char* ptr = file_name_.data();

	strcpy(ptr, File_Directory.c_str());
	ptr += File_Directory.length();

	if (File_Directory.back() != '\\' && File_Directory.back() != '/') {
		strcat(ptr, "\\");
		++ptr;
	}

	strcat(ptr, File_Name.c_str());
	ptr += File_Name.length();

	if (File_Ext.front() != '.') {
		strcat(ptr, ".");
		++ptr;
	}

	strcat(ptr, File_Ext.c_str());

	file_ = CreateFile(file_name_.data(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_NEW, 
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (file_ == INVALID_HANDLE_VALUE) {
		file_ = CreateFile(file_name_.data(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if (file_ == INVALID_HANDLE_VALUE) {
			ML_ASSERT(false, "CreateFile failed.")(file_name_.data());
			return ReturnCode::Failure;
		}

		SetFilePointer(file_, 0, nullptr, FILE_END);
	}

	fmt_date_ = Format_Date;
	strcpy(endl_.data(), Endline_Sequence.c_str());
	max_entry_len_ = Max_Entry_Length;
	return ReturnCode::Success;
}


void BasicFileWriter::Write(const char* Entry, const sysclock_timepoint Timestamp)
{
	if (file_ == INVALID_HANDLE_VALUE) {
		ML_ASSERT(this->file_ != INVALID_HANDLE_VALUE, "Logging file handle is invalid.")();
		return;
	}

	uint32_t entry_len = strlen(Entry);

	std::array<char, 10240> buffer;
	buffer[0] = 0;

	if (this->fmt_date_) {
		std::tm tm_;

		std::time_t tt = std::chrono::system_clock::to_time_t(Timestamp);
		localtime_s(&tm_, &tt);

		strftime(buffer.data(), buffer.size(), "[%Y %b %d %H:%M:%S]\t", &tm_);
	}

	uint32_t len = strlen(buffer.data());

	uint32_t full_len = entry_len + len + strlen(this->endl_.data());
	if (full_len > this->max_entry_len_) {
		const std::string truncated_str("... (TRUNCATED)");

		uint32_t new_len = this->max_entry_len_ - (len + strlen(this->endl_.data())) - truncated_str.length();

		strncat(buffer.data() + len, Entry, new_len);
		len += new_len;
		buffer[len] = 0;

		strcat(buffer.data() + len, truncated_str.c_str());
		len += truncated_str.length();

		strcat(buffer.data() + len, this->endl_.data());
		len += strlen(this->endl_.data());
	}
	else {
		sprintf(buffer.data() + len, "%s%s", Entry, this->endl_.data());
		len += entry_len + strlen(this->endl_.data());
	}

	DWORD bytes_written;
	WriteFile(file_, buffer.data(), len, &bytes_written, nullptr);
}


void BasicFileWriter::Close()
{
	if (file_ != INVALID_HANDLE_VALUE) {
		CloseHandle(file_);
	}
}
} // namespace log
} // namespace ml