#ifndef AIENGINEER_H
#define AIENGINEER_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "ManhattanDistance.h"
#include <list>
#include "Enemy.h"
#include "Timer.h"

/**
	\brief Componete IA que se move para ponto de destino
*/
class AIEngineer : public Component, public TileMapObserver
{
	public:
		/**
			\brief Construtor
			\param speed Velocidade de movimento, cujo sentido é para baixo.
			\param dest tile de destino.
			\param associado objeto associado a essa IA.
			Instancia o componente.
		*/
		AIEngineer(float speed, int dest, TileMap& tilemap, GameObject &associated,WaveManager& wManager);
		~AIEngineer();
		/**
			\brief Atualiza estado.
			\param dt Intervalo de tempo desde a última chamada.
			
			Instancia o componente.
		*/
		void Update(float dt);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o oMapChangedbjetivo de identificar que tipo de componente é.
		*/
		bool Is(ComponentType type) const;
		void NotifyTileMapChanged(int tilePosition);
	private:

		enum AIState{WALKING,WALKING_SLOWLY,BUILDING_BARRIER,STUNNED,STATE_NUM};
		enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,SMOKE,NOT_SMOKE,STUN,NOT_STUN,EVENT_NUM}; 

		AIEvent ComputeEvents();

		float speed;/**< Velocidade de movimento do GameObject com esse componente.*/
		float lastDistance;
		float actualTileweight;
		Vec2 vecSpeed;
		int destTile;/**< indice do tile de destino*/
		std::shared_ptr<std::vector<int>> path;/**< Caminho a ser executado pela IA*/
		uint pathIndex;
		ManhattanDistance *heuristic;/**<Heuristica a ser utilizada pelo A* no calculo do caminho*/
		std::map<int, double> tileWeightMap;
		Vec2 tempDestination;
		TileMap& tileMap;
		GameObject &associated;
		WaveManager& waveManager;
		Timer getPathTimer;
		int randomMaxTimer;

		AIState actualState;
		AIState dfa[AIState::STATE_NUM][AIEvent::EVENT_NUM]; 
};

#endif 
