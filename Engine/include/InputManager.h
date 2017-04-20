#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include<SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
#else
	#error "Unknown compiler"
#endif

#include "Vec2.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_ALT_KEY SDLK_LALT
#define LEFT_CTRL_KEY SDLK_LCTRL
#define LEFT_SHIFT_KEY SDLK_LSHIFT
#define ESPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define MIDDLE_MOUSE_BUTTON SDL_BUTTON_MIDDLE


class InputManager
{
	public:
		void Update(void);
		bool KeyPress(int key) const;
		bool KeyRelease(int key) const;
		bool IsKeyDown(int key) const;
		bool MousePress(int button) const;
		bool MouseRelease(int button) const;
		bool IsMouseDown(int button) const;
		bool IsMouseScrolling(void) const;
		int GetMouseX(void) const;
		int GetMouseY(void) const;
		Vec2 GetMousePos(void) const;
		Vec2 MouseScroll(void) const;
		bool QuitRequested(void) const;
		static InputManager& GetInstance(void);
	private:
		InputManager();
		~InputManager();
		bool mouseState[6];
		int mouseUpdate[6];
		bool quitRequested;
		int updateCounter;
		int mouseX;
		int mouseY;
		bool keyState[416];
		int keyUpdate[416];
		int mouseScroolUpdate;
//		unsigned int
		Vec2 mouseScroolState;
};

#endif // INPUTMANAGER_H
