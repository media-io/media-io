
#include "Window.hpp"
#include "tools.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>

#define MEDIAIO_QUIT_EVENT (SDL_USEREVENT + 2)
#define QUEUE_SIZE 50
#define REFRESH_RATE 0.01

Reader* Window::_reader = NULL;
std::vector<MioQueue<ImageFrame>> Window::_image_queues;
std::vector<MioQueue<AudioFrame>> Window::_audio_queues;

long int Window::_readFrameIndex = 0;
long int Window::_displayFrameIndex = 0;
bool Window::_audio_enabled = true;
bool Window::_info_displayed = false;
TTF_Font* Window::_font = NULL;

SDL_Thread* read_tid = NULL;
bool terminate = false;

static bool is_full_screen;
static const char* window_title = "Media-IO Player";

static int default_width  = 640;
static int default_height = 480;
static int screen_width  = 0;
static int screen_height = 0;
static int paused = false;
static int force_refresh = false;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;

static SDL_Surface *surface;
static Uint16 pixels[16*16] = {
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2,
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2,
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xf38b, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xf38b, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xf38b, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xfbd3, 0xf9c2,
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2,
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2,
	0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2, 0xf9c2
};

Window::Window(Reader& reader, bool audio_enabled)
{
	_reader = &reader;

	TTF_Init();
	_font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 30);

	_audio_enabled = audio_enabled;

	int flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
	_image_queues.push_back(MioQueue<ImageFrame>(QUEUE_SIZE));
	if (_audio_enabled){
		flags |= SDL_INIT_AUDIO;
		_audio_queues.push_back(MioQueue<AudioFrame>(QUEUE_SIZE * 100));
		_audio_queues.push_back(MioQueue<AudioFrame>(QUEUE_SIZE * 100));
	}
	if(SDL_Init(flags)){
		std::cerr << "Could not initialize SDL - " << SDL_GetError() << std::endl;
		return;
	}

	SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
	SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

	read_tid = SDL_CreateThread(read_thread, "read_thread", NULL);

	int w, h;

	if(screen_width == 0) {
		w = screen_width;
		h = screen_height;
	} else {
		w = default_width;
		h = default_height;
	}

	if (!window) {
		int flags = SDL_WINDOW_SHOWN;
		flags |= SDL_WINDOW_BORDERLESS;

		if (is_full_screen)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		// if (borderless)
			// flags |= SDL_WINDOW_BORDERLESS;
		else
			flags |= SDL_WINDOW_RESIZABLE;

		window = SDL_CreateWindow(window_title, 0, 0, w, h, flags);
		surface = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		if(window) {
			// The icon is attached to the window pointer
			SDL_SetWindowIcon(window, surface);
			SDL_FreeSurface(surface);
			SDL_RendererInfo info;
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer) {
				std::cerr << "Failed to initialize a hardware accelerated renderer: " << SDL_GetError() << std::endl;
				renderer = SDL_CreateRenderer(window, -1, 0);
			}
			if (renderer) {
				if (!SDL_GetRendererInfo(renderer, &info)){
					// std::cout << "Initialized " << info.name << " renderer." << std::endl;
				}
			}
		}
	} else {
		SDL_SetWindowSize(window, w, h);
	}

	SDL_AudioSpec wanted;

	/* Set the audio format */
	wanted.freq = 48000;
	wanted.format = AUDIO_S32;
	wanted.channels = 1;    /* 1 = mono, 2 = stereo */
	wanted.samples = 1920;  /* Good low-latency value for callback */
	wanted.callback = fill_audio;
	wanted.userdata = NULL;

	/* Open the audio device, forcing the desired format */
	if(SDL_OpenAudio(&wanted, NULL) < 0) {
		std::cerr << "Couldn't open audio: %s " << SDL_GetError() << std::endl;
		return;
	}
	SDL_PauseAudio(0);
}

int Window::read_thread(void *arg) {
	for(;;) {
		for (int stream_index = 0; stream_index < 2; ++stream_index)
		{
			if(stream_index == 0)
			{
				ImageFrame* frame = new ImageFrame();
				_reader->readNextImageFrame(*frame, stream_index);

				_image_queues.at(0).push(frame);

				// update_console_status();
				while(_image_queues.at(0).is_full())
				{
					mio_usleep((int64_t)(1000.0));
					if(terminate)
						return 0;
				}
			}
			else
			{
				AudioFrame* frame = new AudioFrame();
				_reader->readNextAudioFrame(*frame, stream_index);

				_audio_queues.at(stream_index - 1).push(frame);

				// update_console_status();
				while(_audio_queues.at(stream_index - 1).is_full())
				{
					mio_usleep((int64_t)(1000.0));
					if(terminate)
						return 0;
				}
			}
		}
		_readFrameIndex += 1;

		if(terminate)
			return 0;
	}
}

static int realloc_texture(Uint32 new_format, SDL_BlendMode blendmode, int new_width, int new_height)
{
	Uint32 format;
	int access, w, h;
	if (SDL_QueryTexture(texture, &format, &access, &w, &h) < 0 || new_width != w || new_height != h || new_format != format) {
		SDL_DestroyTexture(texture);
		if (!(texture = SDL_CreateTexture(renderer, new_format, SDL_TEXTUREACCESS_STREAMING, new_width, new_height)))
			return -1;
		if (SDL_SetTextureBlendMode(texture, blendmode) < 0)
			return -1;

		SDL_SetWindowSize(window, new_width, new_height);
		// std::cout << "Created " << new_width << "x" << new_height << " texture with " << SDL_GetPixelFormatName(new_format) << "." << std::endl;
	}
	return 0;
}

clock_t previous_frame_time = clock();

void Window::video_refresh()
{
	ImageFrame* frame = nullptr;
	clock_t current_diff = clock() - previous_frame_time;
	double remaining_time = (((float)current_diff)/CLOCKS_PER_SEC) - (1.f / 50.f);
	
	if(remaining_time < 0) {
		frame = _image_queues.at(0).front();
	}
	else {
		frame = _image_queues.at(0).pop();
		previous_frame_time = clock();
	}

	if(frame != nullptr){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderClear(renderer);
		Uint32 sdl_pix_fmt = SDL_PIXELFORMAT_IYUV;
		SDL_BlendMode sdl_blendmode = SDL_BLENDMODE_NONE;

		size_t width = frame->components[0].width;
		size_t height = frame->components[0].height;

		realloc_texture(sdl_pix_fmt, sdl_blendmode, width, height);
		SDL_UpdateYUVTexture(texture, NULL,
			(const Uint8 *)frame->components[0].data, frame->components[0].width,
			(const Uint8 *)frame->components[1].data, frame->components[1].width,
			(const Uint8 *)frame->components[2].data, frame->components[2].width
		);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = width;
		rect.h = height;

		SDL_Rect display_rect;
		display_rect.x = 0;
		display_rect.y = 0;
		display_rect.w = width;
		display_rect.h = height;

		SDL_RenderCopy(renderer, texture, &rect, &display_rect);

		if(_info_displayed)
		{
			SDL_Rect back_bar;
			back_bar.x = 5;
			back_bar.y = 5;
			back_bar.w = 100;
			back_bar.h = 40;
			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
			SDL_RenderFillRect(renderer, &back_bar);

			size_t image_size = _image_queues.at(0).get_size();
			size_t image_fill = _image_queues.at(0).get_fill_size();

			SDL_Rect image_buffer;
			image_buffer.x = 5;
			image_buffer.y = 5;
			image_buffer.w = 100.0 * image_fill / image_size;
			image_buffer.h = 20;
			SDL_SetRenderDrawColor(renderer, 55, 201, 34, 128);
			SDL_RenderFillRect(renderer, &image_buffer);

			size_t audio_size = _audio_queues.at(0).get_size();
			size_t audio_fill = _audio_queues.at(0).get_fill_size();

			SDL_Rect audio_buffer;
			audio_buffer.x = 5;
			audio_buffer.y = 25;
			audio_buffer.w = 100.0 * audio_fill / audio_size;
			audio_buffer.h = 20;
			SDL_SetRenderDrawColor(renderer, 55, 201, 34, 128);
			SDL_RenderFillRect(renderer, &audio_buffer);

			if(_font)
			{
				int w, h;
				SDL_GetWindowSize(window, &w, &h);

				SDL_Rect back_tc;
				back_tc.x = (0.5 * w) - 55;
				back_tc.y = h - 30;
				back_tc.w = 110;
				back_tc.h = 25;
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
				SDL_RenderFillRect(renderer, &back_tc);

				std::stringstream ss;
				{
					ss << std::setfill('0');
					float fps = 25.0;
					int s = _displayFrameIndex / fps;
					int m = s / 60;
					int h = m / 60;
					int frames = _displayFrameIndex % (int)fps;
					int seconds = s % 60;
					int minutes = m % 60;
					int hours = h % 24;
					ss << std::setw(2) << hours << ":";
					ss << std::setw(2) << minutes << ":";
					ss << std::setw(2) << seconds << ":";
					ss << std::setw(2) << frames;
				}

				SDL_Color color = {255, 255, 255};
				SDL_Surface* surfaceMessage = TTF_RenderText_Blended(_font, ss.str().c_str(), color);
				SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

				SDL_Rect text_tc;
				text_tc.x = (0.5 * w) - 50;
				text_tc.y = h - 30;
				text_tc.w = 100;
				text_tc.h = 25;

				SDL_RenderCopy(renderer, message, NULL, &text_tc);
			}
		}

		_displayFrameIndex += 1;

		update_console_status();
		// delete frame;

		SDL_RenderPresent(renderer);
	}
}

static void do_exit()
{
	terminate = true;
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);

	SDL_CloseAudio();
	int threadReturnValue;
	SDL_WaitThread(read_tid, &threadReturnValue);

	SDL_Quit();
	exit(0);
}

static void toggle_full_screen()
{
	is_full_screen = !is_full_screen;
	SDL_SetWindowFullscreen(window, is_full_screen ? SDL_WINDOW_FULLSCREEN_DESKTOP: 0);
}

void Window::refresh_loop_wait_event(SDL_Event *event) {
	
	double remaining_time = 0;
	SDL_PumpEvents();
	while (!SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT)) {
		if (remaining_time > 0)
			mio_usleep((int64_t)(remaining_time * 1000000.0));
		remaining_time = REFRESH_RATE;

		if (!paused || force_refresh){
			video_refresh();
			force_refresh = false;
		}
		SDL_PumpEvents();
	}
}

void Window::fill_audio(void *udata, Uint8 *stream, int len)
{
	if(paused)
	{
		memset(stream, 0, len);
		return;
	}
	AudioFrame* frame = _audio_queues.at(0).pop();
	if(frame != nullptr)
	{
		auto channel = frame->channels[0];
		memcpy(stream, channel.data, len);
	}
}

template<class T>
std::string get_bar(const T& queue)
{
	size_t size = queue.get_size();
	size_t fill = queue.get_fill_size();

	int ratio = 10.0 * fill / size;
	std::string bar;
	bar.insert(0, 10 - ratio, ' ');
	for(int i = 0; i < ratio; ++i)
	{
		bar.insert(0, "\u2588");
	}
	bar.insert(0, "[");
	bar += "]";

	return bar;
}

void Window::update_console_status()
{
	// std::string image_bar = get_bar(_image_queues.at(0));
	// std::string audio_bar = get_bar(_audio_queues.at(0));
	// std::cout << "\r" << image_bar << " " << audio_bar << " frame: " << _displayFrameIndex << std::flush;
	std::cout << "\r" << "frame: " << _displayFrameIndex << std::flush;
}

void Window::launch()
{
	SDL_Event event;

	for (;;) {
		refresh_loop_wait_event(&event);
		switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
					case SDLK_q:
						do_exit();
						break;
					case SDLK_f:
						toggle_full_screen();
						force_refresh = true;
						break;
					case SDLK_p:
					case SDLK_SPACE:
						paused = !paused;
						break;
					case SDLK_s: // S: Step to next frame
						// step_to_next_frame(cur_stream);
						break;
					case SDLK_i:
						_info_displayed = !_info_displayed;
						break;
					default:
						break;
				}
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						// std::cout << "resize window " << event.window.data1 << " x " <<  event.window.data2 << std::endl;
						screen_width  = event.window.data1;
						screen_height = event.window.data2;
						if (texture) {
							SDL_DestroyTexture(texture);
							texture = NULL;
						}
					case SDL_WINDOWEVENT_EXPOSED:
						force_refresh = true;
				}
				break;
			case SDL_QUIT:
			case MEDIAIO_QUIT_EVENT: {
				do_exit();
				break;
			}
			default:
				break;
		}
	}
}
