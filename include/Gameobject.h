#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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

#include "Rect.h"
#include "string"

using std::string;

class GameObject
{
	public:
		GameObject(void);
		virtual ~GameObject(void);
		virtual void Update(float dt)=0;
		virtual void Render(void)=0;
		virtual bool IsDead(void)=0;
		virtual void NotifyCollision(GameObject &other)=0;
		virtual bool Is(string type)=0;
		Rect box;
		float rotation;
	private:

};

#endif // GAMEOBJECT_H
