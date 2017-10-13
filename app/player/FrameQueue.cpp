#include "FrameQueue.hpp"

FrameQueue::FrameQueue(size_t max_size):
	_max_size(max_size)
{
}

FrameQueue::~FrameQueue()
{}

size_t FrameQueue::push(Frame* frame)
{
	SDL_LockMutex(_mutex);
	_frames.push_back(frame);
	SDL_CondSignal(_cond);
	SDL_UnlockMutex(_mutex);
	return _max_size - _frames.size();
}

Frame* FrameQueue::pop()
{
	SDL_LockMutex(_mutex);
	Frame* ptr = nullptr;
	if(_frames.size() > 0){
		ptr = _frames.front();
		_frames.erase(_frames.begin());
	}
	SDL_CondSignal(_cond);
	SDL_UnlockMutex(_mutex);
	return ptr;
}
