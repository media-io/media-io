#ifndef _AVPLAY_WINDOW_HPP_
#define _AVPLAY_WINDOW_HPP_

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include <mediaio/reader/Reader.hpp>
#include "MioQueue.hpp"

struct _TTF_Font;

class Window
{
public:
	Window(Reader& reader, bool audio_enabled = true);

	void launch();

private:
	static int read_thread(void *arg);
	static void event_loop();

	static void refresh_loop_wait_event(SDL_Event* event);
	static void video_refresh();

	static void fill_audio(void *udata, Uint8 *stream, int len);

	static void update_console_status();

	static Reader*                            _reader;
	static std::vector<MioQueue<ImageFrame>>  _image_queues;
	static std::vector<MioQueue<AudioFrame>>  _audio_queues;

	static _TTF_Font*                          _font;

	static long int                           _readFrameIndex;
	static long int                           _displayFrameIndex;
	static bool                               _audio_enabled;
	static bool                               _info_displayed;
};

#endif
