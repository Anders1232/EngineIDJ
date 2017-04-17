#ifndef RECT_H
#define RECT_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include<SDL2/SDL_image.h>
#else
	#error "Unknown compiler"
#endif

#include "Vec2.h"

class Rect
{
	public:
		Rect(void);
		Rect(float x, float y, float w, float h);
		operator SDL_Rect() const;
		operator Vec2 () const;
		Rect operator+(Vec2 const &a) const;
		Rect operator-(Vec2 const &a) const;
//		SDL_Rect operator-(SDL_Rect const &b) const;
		Rect operator=(Vec2 const &a);
		Rect operator*(float const zoom)const;
		Vec2 Center(void) const;
		void SetWidthAndHeight(Vec2 const &vec);
		float x,y, w, h;
};

#endif // RECT_H
