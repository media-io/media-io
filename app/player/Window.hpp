#ifndef _AVPLAY_WINDOW_HPP_
#define _AVPLAY_WINDOW_HPP_

#include <string>
#include <SDL2/SDL.h>

#include "Reader.hpp"

class Window
{
public:
	Window(Reader& reader);

	void launch();

private:
	static int read_thread(void *arg);
	static void event_loop();

	static void refresh_loop_wait_event(SDL_Event* event);
	static void video_refresh();

	static Reader* _reader;

	static long int _readFrameIndex;
	static long int _displayFrameIndex;
};

#endif
