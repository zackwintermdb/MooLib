#pragma once

#include "FileSystem.h"

namespace ml {

class File
{
private:
	Handle m_handle;
	FileSystem::OpenMode m_mode;
	string256 m_filename;
	uint64_t m_position;
	uint64_t m_size;

public:
	File();
	File(const char* filename, FileSystem::OpenMode mode);
	virtual ~File();

	bool Open(const char* filename, FileSystem::OpenMode mode);
	void Close();
	bool Delete();

	uint32_t Read(void* data, uint32_t length);
	uint32_t Write(const void* data, uint32_t length);

	template <typename T>
	inline uint32_t Read(T& object);
	template <typename T>
	inline uint32_t Write(const T& object);

	bool Seek(int64_t delta, FileSystem::SeekType type=FileSystem::SeekType::Current);

	inline bool IsValid() const;
	inline uint64_t GetPosition() const;
	inline const char* GetFilename() const;
	inline FileSystem::OpenMode GetMode() const;
	inline uint64_t GetSize() const;

private:
	bool _open();
};

#include "File.inl"

} // namespace ml