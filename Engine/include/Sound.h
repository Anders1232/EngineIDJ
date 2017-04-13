#ifndef SOUND_H
#define SOUND_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
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

#include <memory>

#include <string>

using std::string;

class Sound
{
	public:
		Sound();
		Sound(string file);
		void Play(int times);
		void Stop(void);
		void Open(string file);
		bool IsOpen(void);
	private:
		std::shared_ptr<Mix_Chunk> sound;
		int channel;
};

#endif // SOUND_H
