#ifndef _MEDIAIO_PLAYER_MIO_QUEUE_HPP_
#define _MEDIAIO_PLAYER_MIO_QUEUE_HPP_

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include <mediaio/api/data/image_frame.h>

template<class T>
class MioQueue
{
public:
	MioQueue(size_t max_size);
	~MioQueue();

	size_t get_size(){ return _max_size; }
	size_t get_fill_size(){ return _frames.size(); }
	size_t is_full(){ return _frames.size() == _max_size; }

	size_t push(T* frame);
	T* pop();

private:
	std::vector<T*> _frames;
	size_t                   _max_size;
	SDL_mutex*               _mutex;
	SDL_cond*                _cond;
};

template<class T>
MioQueue<T>::MioQueue(size_t max_size):
	_max_size(max_size),
	_mutex(nullptr),
	_cond(nullptr)
{
}

template<class T>
MioQueue<T>::~MioQueue()
{}

template<class T>
size_t MioQueue<T>::push(T* frame)
{
	SDL_LockMutex(_mutex);
	_frames.push_back(frame);
	SDL_CondSignal(_cond);
	SDL_UnlockMutex(_mutex);
	return _max_size - _frames.size();
}

template<class T>
T* MioQueue<T>::pop()
{
	SDL_LockMutex(_mutex);
	T* ptr = nullptr;
	if(_frames.size() > 0){
		ptr = _frames.front();
		_frames.erase(_frames.begin());
	}
	SDL_CondSignal(_cond);
	SDL_UnlockMutex(_mutex);
	return ptr;
}


#endif
