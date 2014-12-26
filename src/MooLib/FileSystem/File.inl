template <typename T>
uint32_t File::Read(T& object)
{
	return Read(&object, sizeof(T));
}


template <typename T>
uint32_t File::Write(const T& object)
{
	return Write(&object, sizeof(T));
}


inline bool File::IsValid() const
{
	return m_handle.IsValid();
}


inline uint64_t File::GetPosition() const
{
	return m_position;
}


inline const char* File::GetFilename() const
{
	return m_filename.data();
}


inline FileSystem::OpenMode File::GetMode() const
{
	return m_mode;
}


inline uint64_t File::GetSize() const
{
	return m_size;
}