#include "pch.h"
#include "Threading.h"

namespace ml {

// ---------------------------------------------------------------------------------------------------------------------
// class Mutex implementation
// ---------------------------------------------------------------------------------------------------------------------
Mutex::Mutex()
{
#ifdef _OPENMP
	omp_init_lock(&handle_);
#else 
	InitializeCriticalSectionEx(&handle_, 4096, CRITICAL_SECTION_NO_DEBUG_INFO);
#endif
}


Mutex::~Mutex()
{
#ifdef _OPENMP
	omp_destroy_lock(&handle_);
#else 
	DeleteCriticalSection(&handle_);
#endif
}


void Mutex::Lock()
{
#ifdef _OPENMP
	omp_set_lock(&handle_);
#else 
	EnterCriticalSection(&handle_);
#endif
}


void Mutex::Unlock()
{
#ifdef _OPENMP
	omp_unset_lock(&handle_);
#else 
	LeaveCriticalSection(&handle_);
#endif
}



// ---------------------------------------------------------------------------------------------------------------------
// class Lock implementation
// ---------------------------------------------------------------------------------------------------------------------
Lock::Lock(Mutex& Mutex_) : mutex_(Mutex_)
{
	mutex_.Lock();
}


Lock::~Lock()
{
	mutex_.Unlock();
}
} // namespace ml