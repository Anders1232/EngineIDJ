#ifndef AIGPRINTPATH_H
#define AIGPRINTPATH_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "ManhattanDistance.h"
#include "Camera.h"
#include <list>

/**
	\brief Componete IA que se move para ponto de destino
*/
class AIPrintPath : public Component
{
	public:
		/**
			\brief Construtor
			\param dest tile de destino.
			Instancia o componente.
		*/
		AIPrintPath(TileMap& tilemap,GameObject &associated);
		/**
			\brief Atualiza estado.
			\param associated GameObject que contém esse componente.
			
			Instancia o componente.
		*/
		void Update(float dt);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o objetivo de identificar que tipo de componente é.
		*/
		bool Is(ComponentType type) const;
	private:
		int dest;/**< indice do tile de destino*/
		TileMap& tilemap;/**< indice do tile de destino*/
		std::shared_ptr<std::vector<int>> path;/**< Caminho a ser executado pela IA*/
		ManhattanDistance *heuristic;/**<Heuristica a ser utilizada pelo A* no calculo do caminho*/
		GameObject &associated;
};

#endif 
