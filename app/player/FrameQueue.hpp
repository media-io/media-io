
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include <mediaio/api/data/frame.h>

class FrameQueue
{
public:
	FrameQueue(size_t max_size);
	~FrameQueue();

	size_t push(Frame* frame);
	Frame* pop();

private:
	std::vector<Frame*> _frames;
	size_t _max_size;
	SDL_mutex* _mutex;
	SDL_cond* _cond;
};
