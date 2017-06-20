#ifndef AIMEDIC_H
#define AIMEDIC_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "ManhattanDistance.h"
#include <list>

/**
	\brief Componete IA que se move para ponto de destino
*/
class AIMedic : public Component
{
	public:
		/**
			\brief Construtor
			\param speed Velocidade de movimento, cujo sentido é para baixo.
			\param dest tile de destino.
			\param associado objeto associado a essa IA.
			Instancia o componente.
		*/
		AIMedic(float speed,int dest,TileMap* tilemap,GameObject &associated);
		/**
			\brief Atualiza estado.
			\param dt Intervalo de tempo desde a última chamada.
			
			Instancia o componente.
		*/
		void Update(float dt);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o objetivo de identificar que tipo de componente é.
		*/
		bool Is(ComponentType type) const;
	private:

		enum AIState{WALKING,WALKING_SLOWLY,WAITING,STUNNED,STATE_NUM};
		enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,SMOKE,NOT_SMOKE,STUN,NOT_STUN,EVENT_NUM}; 

		AIEvent ComputeEvents();

		float speed;/**< Velocidade de movimento do GameObject com esse componente.*/
		Vec2 vecSpeed;
		int destTile;/**< indice do tile de destino*/
		std::list<int> path;/**< Caminho a ser executado pela IA*/
		ManhattanDistance *heuristic;/**<Heuristica a ser utilizada pelo A* no calculo do caminho*/
		std::map<int, double> tileWeightMap;
		Vec2 tempDestination;
		TileMap* tilemap;
		GameObject &associated;

		AIState actualState;
		AIState dfa[AIState::STATE_NUM][AIEvent::EVENT_NUM]; 
};

#endif 