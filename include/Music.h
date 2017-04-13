#ifndef MUSIC_H
#define MUSIC_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
#else
	#error "Unknown compiler"
#endif

#include <string>
#include "Resources.h"
#include "Error.h"

#define MUSIC_FADE_OUT_TIME_MSEC (2000)

using std::string;

class Music
{
	public:
		Music();
		Music(string file);
		void Play(int times);
		void Stop(void);
		void Open(string file);
		bool IsOpen(void)const;
	private:
		std::shared_ptr<Mix_Music> music;
};

#endif // MUSIC_H
