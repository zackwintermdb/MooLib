inline bool Handle::IsValid() const
{
	return m_handle != INVALID_HANDLE_VALUE;
}


inline HANDLE Handle::GetNative() const
{
	return m_handle;
}