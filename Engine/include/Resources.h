#ifndef RESOURCES_H
#define RESOURCES_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#else
	#error "Unknown compiler"
#endif

#include <string>
#include <unordered_map>
#include <memory>

using std::string;

class Resources
{
	public:
		static std::shared_ptr<SDL_Texture> GetImage(string file);
		static std::shared_ptr<Mix_Music> GetMusic(string file);
		static std::shared_ptr<Mix_Chunk> GetSound(string file);
		static std::shared_ptr<TTF_Font> GetFont(string file, int fontSize);
		static void ClearResources(void);
	private:
		Resources();
		static void ClearImages(void);
		static void ClearMusic(void);
		static void ClearSound(void);
		static void ClearFonts(void);
		static std::unordered_map<string, std::shared_ptr<SDL_Texture>> imageTable;
		static std::unordered_map<string, std::shared_ptr<Mix_Music>> musicTable;
		static std::unordered_map<string, std::shared_ptr<Mix_Chunk>> soundTable;
		static std::unordered_map<string, std::shared_ptr<TTF_Font>> fontTable;
};

#endif // RESOURCES_H
