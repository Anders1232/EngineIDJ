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

/**
	\brief Classe que modela o todo-poderoso Jogo
	
	Contém o loop principal do jogo, gerencia a pilha de estados do jogo, responsável por gerenciar a janela(no momento apenas informa as dimensões da janela).
	Também calcula é o que calcula o delta time que é enviado ao update de várias entidades do jogo.
*/
class Game
{
	public:
		/**
			\brief Construtor
			\param title Nome da janela.
			\param width Largura da janela em pixels.
			\param height Altura da janela em pixels
			
			Para fins de detecção de problemas futuros, a versão da SDL para a qual o jogo foi compilado e a versão na qual a SDL está sendo linkada no carregamento.
			A deferença entre essas versões podem ser a causa de alguns bugs.
			As seguintes tarefas são feitas:
				- O contador de ticks é inicado.
				- Verifica-se se já existe algum outra instância de jogo, se existir o jogo é fechado. Só deve haver uma instncia do jogo.
				- A SDL é iniciada.
				- A janela é criada com o o títlulo title, com dimensões width x width.
				- O SDL_Renderer é inicializado.
				- O mixer é inicializado.
				- O sistema de áudio é inicializado(é uma inicialização diferente do mixer)
				- O subsistema de fontes é inicializado.
				- A variável storedState é inicializada com nullptr.
		*/
		Game(std::string title,int width, int height);
		/**
			\brief Destrutor
			
			A pilha de estados é esvaziada. Se tiver algum estado em storedState ele será deletado.
			O ClearResources é chamado e os sistemas da SDL que foram inicializados são destruídos na ordem inversa em que foram inicializados. Par garantir que primeiro os subsistemas que não tem dependêntes sejam desalocados primeiros.
		*/
		~Game();
		/**
			\brief Obter instância do Game

			Esquema básico do singleton. Retorna ainstância do singleton. Não se faz a chegagem por motrivos cronológicos
		*/
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
