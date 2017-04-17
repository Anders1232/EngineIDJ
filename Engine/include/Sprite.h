#ifndef SPRITE_H
#define SPRITE_H

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


#include <string>
#include <memory>

class Sprite
{
	public:
		Sprite(void);
//		Sprite(std::string file);
		Sprite(std::string file, float frameTime=1, int frameCount=1);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y, float angle=0, bool zoom= false) const;
//		void Rotate(double angle);
		int GetWidth(void) const;
		int GetHeight(void) const;
		std::shared_ptr<SDL_Texture> GetTexture(void) const;
		bool IsOpen(void) const;
		void Update(float dt);
		void SetFrame(int frame);
		void SetFrameCount(int frameCount);
		void SetFrameTime(float frameTime);
		void SetScaleX(float scale);
		void SetScaleY(float scale);
		void SetScale(float scale);
		void ScaleX(float scale);
		void ScaleY(float scale);
		void Scale(float scale);
	private:
		std::shared_ptr<SDL_Texture> texture;
		int width;
		int height;
		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;
		SDL_Rect clipRect;
//		double angle;
		float scaleX;
		float scaleY;
};


#endif // SPRITE_H
