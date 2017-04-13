#ifndef GAME_H
#define GAME_H

#include <string>
#include <stack>
#include"State.h"
#include "InputManager.h"
#include "Vec2.h"

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <stdint.h>
	typedef uint8_t u_int8_t;
	typedef uint16_t u_int16_t;
	typedef uint32_t u_int32_t;

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

#define MIXER_CHUCK_SIZE 1024


class Game
{
	public:
		Game(std::string title,int width, int height);
		~Game();
		static Game& GetInstance(void);
		SDL_Renderer* GetRenderer(void) const;
		State& GetCurrentState(void) const;
		void Push(State* state);
		void Run(void);
		float GetDeltaTime(void) const;
		Vec2 GetWindowDimensions(void) const;
	private:
		void CalculateDeltaTime(void);
		void UpdateStack(void);

		unsigned int frameStart;
		float dt;
		static Game* instance;
		State* storedState;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::stack<std::unique_ptr<State>> stateStack;
		InputManager &inputManager;
};

#endif // GAME_H
