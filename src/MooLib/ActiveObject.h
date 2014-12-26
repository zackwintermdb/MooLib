#pragma once

#include <concurrent_queue.h>


namespace ml {

typedef std::function<void()> ThreadCallback;


class ActiveObject
{
private:
	Concurrency::concurrent_queue<ThreadCallback> _mq;
	std::thread _thread;
	bool _finished;
	std::condition_variable _cv;
	std::mutex _mut;


public:
	ActiveObject();
	~ActiveObject();

	void Send(ThreadCallback cb);
	void Run();


private:
	void _Finish();


	ML_NO_COPY(ActiveObject);
	ML_NO_ASSIGN(ActiveObject);
};
} // namespace ml

