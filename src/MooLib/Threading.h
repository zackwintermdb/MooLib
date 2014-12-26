#pragma once

#include <omp.h>
#include <thread>


namespace ml {
	
#if _OPENMP
typedef omp_lock_t MutexHandle_t;
#else 
typedef CRITICAL_SECTION MutexHandle_t;
#endif

typedef uint32_t (WINAPI* ThreadProc_t)(void*);


class Mutex
{
private:
	MutexHandle_t handle_;


public:
	Mutex();
	~Mutex();


	void Lock();
	void Unlock();


private:
	ML_NO_COPY(Mutex);
	ML_NO_ASSIGN(Mutex);
};



class Lock
{
private:
	Mutex& mutex_;


public:
	Lock(Mutex& Mutex_);
	~Lock();


private:
	ML_NO_COPY(Lock);
	ML_NO_ASSIGN(Lock);
};
} // namespace ml


/*
class Thread
{
private:
	uintptr_t handle_;
	volatile bool terminating_;
	bool running_;
	Mutex mut_;
	uint32_t id_;

public:
	Thread()
		: handle_(nullptr), terminating_(false), running_(false)
	{

	}

	~Thread()
	{

	}

	bool StartThread(ThreadProc_t func, void* args, bool suspended)
	{
		if (running_)
		{
			return false;
		}

		if (handle_)
		{
			return false;
		}

		handle_ = _beginthreadex(nullptr, 0, func, args, suspended ? CREATE_SUSPENDED : 0, &id_);
	}
};
*/