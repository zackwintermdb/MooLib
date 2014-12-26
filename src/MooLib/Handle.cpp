#include "pch.h"
#include "Handle.h"


namespace ml {
Handle::Handle() : m_handle(INVALID_HANDLE_VALUE)
{
}


Handle::Handle(HANDLE rhs) : m_handle(rhs)
{
}


Handle::~Handle()
{
	this->Close();
}


void Handle::Close()
{
	if (this->IsValid()) {
		CloseHandle(m_handle);
		m_handle = INVALID_HANDLE_VALUE;
	}
}


Handle& Handle::operator=(HANDLE rhs)
{
	m_handle = rhs;
	return *this;
}


bool Handle::operator==(Handle rhs)
{
	return this->m_handle == rhs.m_handle;
}


bool Handle::operator==(HANDLE rhs)
{
	return this->m_handle == rhs;
}


bool Handle::operator!=(Handle rhs)
{
	return this->m_handle != rhs.m_handle;
}


bool Handle::operator!=(HANDLE rhs)
{
	return this->m_handle != rhs;
}
} // namespace ml
