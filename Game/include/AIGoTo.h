#ifndef AIGOTO_H
#define AIGOTO_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "ManhattanDistance.h"
#include <list>

/**
	\brief Componete IA que se move para ponto de destino
*/
class AIGoTo : public Component
{
	public:
		/**
			\brief Construtor
			\param speed Velocidade de movimento, cujo sentido é para baixo.
			\param dest tile de destino.
			Instancia o componente.
		*/
		AIGoTo(float speed,int dest,TileMap& tilemap,GameObject &associated);
		~AIGoTo(void);
		/**
			\brief Atualiza estado.
			\param associated GameObject que contém esse componente.
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
		
		float speed;/**< Velocidade de movimento do GameObject com esse componente.*/
		Vec2 vecSpeed;
		int destTile;/**< indice do tile de destino*/
		std::shared_ptr<std::vector<int>> path;/**< Caminho a ser executado pela IA*/
		uint pathIndex;
		ManhattanDistance *heuristic;/**<Heuristica a ser utilizada pelo A* no calculo do caminho*/
		std::map<int, double> tileWeightMap;
		GameObject &associated;
		Vec2 tempDestination;
		TileMap& tileMap;

};

#endif 
