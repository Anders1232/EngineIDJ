#ifndef TEXT_H
#define TEXT_H

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

#include "Rect.h"
#include <memory>
#include <string>
using std::string;

enum TextStyle
{
	SOLID,
	SHARED,
	BLENDED
};

class Text
{
	public:
		Text
		(
			string fontFile,
			int fontSize,
			TextStyle style,
			SDL_Color color,
			int x= 0,
			int y=0
		);
		~Text();
		void Render(int CameraX=0, int cameraY=0) const;
		void SetPos(int x, int y, bool centerX=false, bool centerY=false);
		void SetText(string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontSize(int fontSize);
		Vec2 GetSize(void)const;
	private:
		void RemakeTexture(void);
		std::shared_ptr<TTF_Font> font;
		SDL_Texture* texture;
		string text;
		TextStyle style;
		int fontSize;
		SDL_Color color;
		Rect box;
};


#include "Resources.h"
#include "Game.h"
#include "Error.h"

#endif // TEXT_H
