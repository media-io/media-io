

#include "FrameQueue.hpp"
#include "Window.hpp"
#include "tools.hpp"
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#define MEDIAIO_QUIT_EVENT (SDL_USEREVENT + 2)
#define FRAME_QUEUE_SIZE 3
#define REFRESH_RATE 0.01

Reader* Window::_reader = NULL;
long int Window::_readFrameIndex = 0;
long int Window::_displayFrameIndex = 0;

SDL_Thread* read_tid = NULL;

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

static FrameQueue frame_queue(10);

Window::Window(Reader& reader)
{
	_reader = &reader;
	bool audio_enable = false;
	int flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;

	if (audio_enable){
		flags |= SDL_INIT_AUDIO;
	}
	if(SDL_Init(flags)){
		std::cout << "Could not initialize SDL - " << SDL_GetError() << std::endl;
		return;
	}

	SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
	SDL_EventState(SDL_USEREVENT, SDL_IGNORE);


	read_tid = SDL_CreateThread(read_thread, "read_thread", NULL);


	int w, h;

	if (screen_width) {
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

		window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		if(window) {
			SDL_RendererInfo info;
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer) {
				std::cout << "Failed to initialize a hardware accelerated renderer: " << SDL_GetError() << std::endl;
				renderer = SDL_CreateRenderer(window, -1, 0);
			}
			if (renderer) {
				if (!SDL_GetRendererInfo(renderer, &info))
					std::cout << "Initialized " << info.name << " renderer." << std::endl;
			}
		}
	} else {
		SDL_SetWindowSize(window, w, h);
	}
}

int Window::read_thread(void *arg) {
	for(;;) {
		Frame* frame = new Frame();
		Window::_reader->readNextFrame(*frame);
		_readFrameIndex += 1;
		frame_queue.push(frame);
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
		std::cout << "Created " << new_width << "x" << new_height << " texture with " << SDL_GetPixelFormatName(new_format) << "." << std::endl;
	}
	return 0;
}

void Window::video_refresh()
{
	Frame* frame = frame_queue.pop();

	if(frame != nullptr){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		Uint32 sdl_pix_fmt = SDL_PIXELFORMAT_IYUV;
		SDL_BlendMode sdl_blendmode = SDL_BLENDMODE_NONE;

		realloc_texture(sdl_pix_fmt, sdl_blendmode, frame->components[0].width, frame->components[0].height);
		SDL_UpdateYUVTexture(texture, NULL,
			(const Uint8 *)frame->components[0].data, frame->components[0].width,
			(const Uint8 *)frame->components[1].data, frame->components[1].width,
			(const Uint8 *)frame->components[2].data, frame->components[2].width
		);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = frame->components[0].width;
		rect.h = frame->components[0].height;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		_displayFrameIndex += 1;
		std::cout << "\rread frame index: " << _readFrameIndex << " display frame index : " << _displayFrameIndex << std::flush;
		delete frame;

		SDL_RenderPresent(renderer);
	}
}

static void do_exit()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

static void toggle_full_screen()
{
	is_full_screen = !is_full_screen;
	SDL_SetWindowFullscreen(window, is_full_screen ? SDL_WINDOW_FULLSCREEN_DESKTOP: 0);
}

void Window::refresh_loop_wait_event(SDL_Event *event) {
	double remaining_time = 0.0;
	SDL_PumpEvents();
	while (!SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT)) {
		if (remaining_time > 0.0)
			mio_usleep((int64_t)(remaining_time * 1000000.0));
		remaining_time = REFRESH_RATE;
		if (!paused || force_refresh){
			video_refresh();
			force_refresh = false;
			remaining_time = 1.0/30.0;
		}

		SDL_PumpEvents();
	}
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
		case MEDIAIO_QUIT_EVENT:
			do_exit();
			break;
		default:
			break;
		}
	}
}
