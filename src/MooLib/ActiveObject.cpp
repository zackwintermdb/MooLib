#include "pch.h"
#include "ActiveObject.h"


namespace ml {

ActiveObject::ActiveObject() 
	: _finished(false)
{
	_thread = std::thread(std::bind(&ActiveObject::Run, this));
}


ActiveObject::~ActiveObject()
{
	this->Send(std::bind(&ActiveObject::_Finish, this));
	if (_thread.joinable()) {
		_thread.join();
	}
}


void ActiveObject::Send(ThreadCallback cb)
{
	_mq.push(cb);
	_cv.notify_one();
}


void ActiveObject::Run()
{
	while (!_finished) {
		std::unique_lock<std::mutex> lk(_mut);
		_cv.wait(lk);
		lk.unlock();

		ThreadCallback cb;
		while (_mq.try_pop(cb)) {
			cb();
		}
	}
}


void ActiveObject::_Finish()
{
	_finished = true;
}
} // namespace ml