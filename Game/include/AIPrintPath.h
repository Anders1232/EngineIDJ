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
		AIPrintPath(int dest,TileMap* tilemap);
		/**
			\brief Atualiza estado.
			\param associated GameObject que contém esse componente.
			
			Instancia o componente.
		*/
		void Update(GameObject &associated,int newDest);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o objetivo de identificar que tipo de componente é.
		*/
		bool Is(ComponentType type) const;
	private:
		int dest;/**< indice do tile de destino*/
		TileMap* tilemap;/**< indice do tile de destino*/
		std::list<int> path;
		ManhattanDistance *heuristic;
};

#endif 