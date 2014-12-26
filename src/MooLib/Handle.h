#pragma once


// RAII handle wrapper
namespace ml {
class Handle
{
private:
	HANDLE m_handle;

public:
	Handle();
	Handle(HANDLE rhs);
	~Handle();

	Handle& operator=(HANDLE rhs);

	bool operator==(Handle rhs);
	bool operator==(HANDLE rhs);
	bool operator!=(Handle rhs);
	bool operator!=(HANDLE rhs);

	inline bool IsValid() const;
	inline HANDLE GetNative() const;
	void Close();
};

#include "Handle.inl"

} // namespace ml