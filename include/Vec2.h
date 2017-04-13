#ifndef VEC2OP_H
#define VEC2OP_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	// linux
#else
	#error "Unknown compiler"
#endif


class Vec2
{
	public:
		Vec2(void);
		Vec2(float x, float y);
		static Vec2 FromPolarCoord(float magentude, float angle);
		Vec2(Vec2 const &b);
		Vec2 operator+(Vec2 const &b)const;
		Vec2 operator-(Vec2 const &b) const;
		Vec2 operator*(float b)const;
		Vec2& operator=(Vec2 const &b);
		Vec2& operator+=(Vec2 const &b);
		Vec2& operator-=(Vec2 const &b);
		Vec2 MemberMult(float const &b)const;
		float Magnitude(void)const;
		void Normalize(void);
		Vec2 Rotate(float angle) const;
		float DistanceTo(Vec2 const &b) const;
		float Inclination(void) const;
		float Inclination(Vec2 const &b) const;
		bool IsInRect(SDL_Rect const &rect) const;
		void SetWidthAndHeight(Vec2 const &vec);
		float x;
		float y;
};

#endif // VEC2OP_H
