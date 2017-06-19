#ifndef AIART_H
#define AIART_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include <list>

/**
	\brief Componete IA que se move para ponto de destino
*/
class AIArt : public Component
{
	public:
		/**
			\brief Construtor
			\param speed Velocidade de movimento, cujo sentido é para baixo.
			\param dest tile de destino.
			Instancia o componente.
		*/
		AIArt(float speed,int dest);
		/**
			\brief Atualiza estado.
			\param associated GameObject que contém esse componente.
			\param dt Intervalo de tempo desde a última chamada.
			
			Instancia o componente.
		*/
		void Update(GameObject &associated, float dt);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o objetivo de identificar que tipo de componente é.
		*/
		bool Is(ComponentType type) const;
	private:

		void Compute();

		float speed;/**< Velocidade de movimento do GameObject com esse componente.*/
		int destTile;/**< indice do tile de destino*/
		std::list<int> path;/**< Caminho a ser executado pela IA*/
		Vec2 tempDestination;
		enum AIState{WALKING,WAITING,FINDINGHEALTH,STUNNED,STATE_NUM};
		enum AIEvent{PATH_BLOCKED,PATH_FREE,FOUNDHEALTH,STUN,NOT_STUN,EVENT_NUM}; 

		AIState actualState;
		AIState dfa[AIState::STATE_NUM][AIEvent::EVENT_NUM]; 
};

#endif 