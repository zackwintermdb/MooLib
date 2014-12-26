#include "pch.h"
#include "File.h"


using namespace ml::FileSystem;

namespace ml {
File::File(const char* filename, FileSystem::OpenMode mode)
	: m_filename(filename), m_mode(mode), m_position(0), m_size(0), m_handle(INVALID_HANDLE_VALUE)
{
	if (!this->_open()) {
		m_handle.Close();
	}
}


File::File()
	: m_mode(OpenMode::None), m_position(0), m_size(0), m_handle(INVALID_HANDLE_VALUE)
{
}


File::~File()
{
}


uint32_t File::Read(void* data, uint32_t length)
{
	ML_ASSERT(IsValid(), "Invalid file handle")();

	DWORD dwBytesRead;
	if (!ReadFile(m_handle.GetNative(), data, length, &dwBytesRead, nullptr)) {
		ML_DBGLOG("ReadFile failed")(GetLastError());
		return 0;
	}

	m_position += dwBytesRead;
	return (uint32_t)dwBytesRead;
}


uint32_t File::Write(const void* data, uint32_t length)
{
	ML_ASSERT(IsValid(), "Invalid file handle")();

	DWORD dwBytesWritten;
	if (!WriteFile(m_handle.GetNative(), data, length, &dwBytesWritten, nullptr)) {
		ML_DBGLOG("WriteFile failed")(GetLastError());
		return 0;
	}

	m_position += dwBytesWritten;
	return (uint32_t)dwBytesWritten;
}


bool File::_open()
{
	DWORD access_mode = 0;
	DWORD share_mode = 0;
	DWORD create_mode = 0;

	if (m_mode & OpenMode::Read) {
		access_mode |= GENERIC_READ;
	}

	if (m_mode & OpenMode::Write) {
		access_mode |= GENERIC_WRITE;
	}

	if (m_mode & OpenMode::Share) {
		share_mode = FILE_SHARE_READ;
	}

	if (m_mode & OpenMode::Create) {
		create_mode = OPEN_ALWAYS;
	}
	else {
		create_mode = OPEN_EXISTING;
	}

	m_handle = CreateFile(m_filename.data(), access_mode, share_mode, nullptr, create_mode, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (!IsValid()) {
		MooLog::Write("Failed to open file: %s", m_filename.data());
		return false;
	}

	LARGE_INTEGER size;
	if (!GetFileSizeEx(m_handle.GetNative(), &size)) {
		MooLog::Write("GetFileSizeEx failed %s", m_filename.data());
		return false;
	}

	m_size = size.QuadPart;

	if (m_mode & OpenMode::Append) {
		if (!this->Seek(0, FileSystem::SeekType::End)) {
			return false;
		}
	}

	return true;
}


bool File::Seek(int64_t delta, FileSystem::SeekType type/*=FileSystem::SeekType::Current*/)
{
	ML_ASSERT(IsValid(), "Invalid file handle")();

	LARGE_INTEGER distance;
	LARGE_INTEGER new_pos;
	DWORD move_method;
	distance.QuadPart = (uint64_t)delta;

	switch(type)
	{
	case FileSystem::SeekType::Current:
		if (m_position + (uint64_t)delta > m_size) {
			return false;
		}
		move_method = FILE_CURRENT;
		break;

	case FileSystem::SeekType::Begin:
		ML_ASSERT(delta >= 0, "Delta must be positive or zero when SeekType::Begin is specified.")(delta);
		if ((uint64_t)delta > m_size || delta < 0) {
			return false;
		}
		move_method = FILE_BEGIN;
		break;

	case FileSystem::SeekType::End:
		ML_ASSERT(delta <= 0, "Delta must be negative or zero when SeekType::End is specified.")(delta);
		if ((uint64_t)abs(delta) > m_size || delta > 0) {
			return false;
		}
		move_method = FILE_END;
		break;

	default:
		ML_ASSERT(false, "invalid FileSystem::SeekType specified.")();
		return false;
	}

	bool ret = SetFilePointerEx(m_handle.GetNative(), distance, &new_pos, move_method) != FALSE;
	if (ret) {
		m_position = new_pos.QuadPart;
	}

	return ret;
}


bool File::Open(const char* filename, FileSystem::OpenMode mode)
{
	this->Close();

	m_filename = filename;
	m_mode = mode;
	bool ret = this->_open();
	if (!ret) {
		m_handle.Close();
	}

	return ret;
}


void File::Close()
{
	m_handle.Close();
	m_position = 0;
	m_size = 0;
}


bool File::Delete()
{
	this->Close();
	if (m_filename.length() == 0) {
		return false;
	}
	return DeleteFileA(m_filename.data()) == TRUE;
}
} // namespace ml
