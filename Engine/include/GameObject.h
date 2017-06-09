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
	#include <SDL2/SDL_image.h>
#else
	#error "Unknown compiler"
#endif
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "ComponentType.h"
#include "Rect.h"

using std::string;
using std::unique_ptr;

#ifndef COMPONENT
class Component;
#endif

#define GAME_OBJECT
/**
	\brief Classe virtual que especifica o funcionamento de um GameObject.
	
	Especifica quais métodos um gameObject deve ter para conseguir ser manipulado corretamente pela engine.
*/
class GameObject{
	public:
		/**
			\brief Construtor
			
			Não é virtual, sua implementação inicializa a rotação com o valor zero. Pode ser usado pelos herdeiros.
		*/
		GameObject(void);
		/**
			\brief Adiciona componente a um gameobjet.
			\param component componente a ser adicionado.
			
		*/
		void AddComponent(Component* component);
		/**
			\brief Remove componente a um gameobjet.
			\param type tipo do componente a ser adicionado.
			
		*/
		void RemoveComponent(ComponentType type);
		/**
			\brief Destrutor
			
			Basicamente é para obrigar quem implementar de usar um destrutor.
		*/
		virtual ~GameObject(void);
		/**
			\brief Atualizar estado.
			\param dt tempo transcorrido desde a última chamada ao método.
			
			No corpo método o GameObject deve atualizar seu estado, utilizando o argumento passado e quaisquer outras funcionalidades que necessitar.
		*/
		virtual void Update(float dt)=0;
		/**
			\brief Renderiza o GameObject.
			
			Esse método deve ter a lógica necessário para ser renderizado na tela.
		*/
		virtual void Render(void)=0;
		/**
			\brief Informa se esse gameObject não precisa mais existir.
			\return Verdadeiro se esse GameObject não é mais necessário, false caso contrário.
			
			Deve ser usado no State que o contém para o eliminar da sua estrutura de manipulação de gameObject e destruí-lo.
		*/
		virtual bool IsDead(void)=0;
		/**
			\brief Solicita que o GameObject seja destruído.
			
			Uma vez que esse método é chamado, futuras chamadas ao IsDead devem retornar verdadeiro.
		*/
		virtual void RequestDelete(void)=0;
		/**
			\brief Notifica Colisão
			\param other Referência para o gameobject com o qual se colidiu.
			
			Deve realizar as ações para tratamento da colisão.
		*/
		virtual void NotifyCollision(GameObject &other)=0;
		/**
			\brief Informa que tipo de GameObject é.
			\param type Tipo com o qual quer se verificar que esse GameObject é.
			\return Verdadeiro se for do tipo perguntado, falso caso contrário;
			
			É usado no tratamento de colisão para que se identifique com quem colidiu.
		*/
		virtual bool Is(string type)=0;
		/**
			\brief Obtém Rect informando a posição renderizada da animação.

			Obtém Rect informando a posição renderizada, computando zoom, escala e posição da câmera.
		*/
		virtual Rect GetWorldRenderedRect(void) const=0;
		Rect box;/**< Posição do GameObject na tela.*/
		float rotation;/**< Rotação do GameObject.*/
	protected:
		std::vector<Component* > components;/**< Vetor de componentes, que provêem funcionalidades adicionais.*/
};

#endif // GAMEOBJECT_H
