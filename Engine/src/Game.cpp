#include "Game.h"
#include "Error.h"
#include "Resources.h"
#include<stdlib.h>
#include<time.h>

Game* Game::instance= nullptr;

Game::Game(std::string title,int width, int height):dt(0.0),  inputManager(InputManager::GetInstance())//, frameStart(SDL_GetTicks())
{
	frameStart= SDL_GetTicks();
	srand(time(NULL));
	if(nullptr != Game::instance)
	{
		Error("Second instantion of the game!");
	}
	Game::instance= this;
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		Error(SDL_GetError());
	}
	int result= IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	if(0 == result)
	{
		Error("Loading IMG_Init failed: " << IMG_GetError());
	}
	if(0 == (result & IMG_INIT_JPG ) )
	{
		Error("Loading IMG_INIT_JPG failed: " << IMG_GetError());
	}
	if(0 == (result & IMG_INIT_PNG) )
	{
		Error("Loading IMG_INIT_PNG failed: " << IMG_GetError());
	}
	if(0 == (result & IMG_INIT_TIF ))
	{
		Error("Loading IMG_INIT_TIF failed: " << IMG_GetError());
	}
	window= SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(nullptr == window)
	{
		Error(SDL_GetError());
	}
	renderer= SDL_CreateRenderer(window, -1, 0);
	if(nullptr == renderer)
	{
		Error(SDL_GetError());
	}
	result= Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	if(0 == result)
	{
		Error("Loading Mix_Init failed: " << Mix_GetError());
	}
/*	if(0 == (result & MIX_INIT_MP3 ) )
	{
		Error("Loading MIX_INIT_MP3 failed: " << Mix_GetError());
	}*/
	if(0 == (result & MIX_INIT_OGG) )
	{
		Error("Loading MIX_INIT_OGG failed: " << Mix_GetError());
	}
	if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIXER_CHUCK_SIZE))
	{
		Error("Loading Mix_OpenAudio failed: " << Mix_GetError());
	}
	if(0 != TTF_Init())
	{
		Error("Loading TTF_Init failed: " << TTF_GetError());
	}
	REPORT_I_WAS_HERE;
	storedState= nullptr;
	REPORT_I_WAS_HERE;
}

Game::~Game()
{
	IMG_Quit();
	if(nullptr != storedState)
	{
		delete storedState;
	}
	while(!stateStack.empty())
	{
		stateStack.pop();
	}
	Resources::ClearResources();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game& Game::GetInstance(void)
{
	return *(Game::instance);
}

State& Game::GetCurrentState(void) const
{
	return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer(void)const
{
	return renderer;
}

void Game::Push(State* state)
{
	if(nullptr != storedState)
	{
		std::cout << WHERE << "Não era para ter um state aqui...\n";
	}
	storedState= state;
}

void Game::Run(void)
{
	if(nullptr !=  storedState)
	{
		stateStack.push(std::unique_ptr<State>(storedState));
		storedState= nullptr;
	}
	else
	{
		return;//jogo terminou
	}
	while(!stateStack.empty())
	{
		if(stateStack.top()->QuitRequested())
		{
			break;
		}
		CalculateDeltaTime();
		inputManager.Update();
		stateStack.top()->Update(GetDeltaTime());
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);
		UpdateStack();
		SDL_Delay(33);
//		SDL_Delay(15);
	}
	while(!stateStack.empty())
	{
		stateStack.pop();
	}
	Resources::ClearResources();
}

void Game::CalculateDeltaTime(void)
{
	u_int32_t newTick= SDL_GetTicks();
	dt=((float)(newTick-frameStart))/1000;//converter de milissegundos para segundos
	frameStart= newTick;
}

float Game::GetDeltaTime(void) const
{
	return dt;
}

void Game::UpdateStack(void)
{
	if(stateStack.top()->PopRequested())
	{
		stateStack.pop();
		Resources::ClearResources();
		if(!stateStack.empty())
		{
			stateStack.top()->Resume();
		}
	}
	if(nullptr != storedState)
	{
		if(!stateStack.empty())
		{
			stateStack.top()->Pause();
		}
		stateStack.push(std::unique_ptr<State>(storedState));
		storedState= nullptr;
	}
}

Vec2 Game::GetWindowDimensions(void) const
{
	Vec2 ret;
	SDL_GetWindowSize(window, (int*)&ret.x, (int*)&ret.y);
	ret.x= *((int*)&ret.x);
	ret.y= *((int*)&ret.y);
	return ret;
}

