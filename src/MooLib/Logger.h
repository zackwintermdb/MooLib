#pragma once

#include "Threading.h"
#include <Shlobj.h>


namespace ml {

typedef std::chrono::system_clock::time_point sysclock_timepoint;

namespace log 
{
	// forward
	class BaseWriter;

	
	enum class ReturnCode
	{
		Success,
		Failure,
		Fatal,
		NotFound,
		AlreadyExists,
		InvalidParameter
	};


	const char* GetRetCodeString(ReturnCode Code);
	
	ReturnCode AddWriter(BaseWriter* Writer_Object);

	void ClearWriters();

	void Write(const char* Entry_Format, ...);

	void Write(const SourceInfo& Source_Info, const char* Entry_Format, ...);

	class BaseWriter
	{
	public:
		BaseWriter();
		virtual ~BaseWriter();

		virtual void Write(const char* Entry, const sysclock_timepoint Timestamp) = 0;
		virtual void Close() = 0;

	private:
		ML_NO_COPY(BaseWriter);
		ML_NO_ASSIGN(BaseWriter);
	};


	class BasicFileWriter : public BaseWriter
	{
	public:
		BasicFileWriter();
		virtual ~BasicFileWriter();

		// max entry len not to exceed 8192
		ReturnCode Init(const std::string& File_Directory, const std::string& File_Name, const std::string& File_Ext, 
			bool Format_Date=true, const std::string& Endline_Sequence="\r\n", uint32_t Max_Entry_Length=4096);
		void Write(const char* Entry, const sysclock_timepoint Timestamp);
		void Close();

	private:
		bool fmt_date_;
		std::array<char, 16> endl_;
		HANDLE file_;
		std::array<char, MAX_PATH> file_name_;
		uint32_t max_entry_len_;

	private:
		ML_NO_COPY(BasicFileWriter);
		ML_NO_ASSIGN(BasicFileWriter);
	};
} // namespace Log
} // namespace ml

namespace MooLog = ml::log;