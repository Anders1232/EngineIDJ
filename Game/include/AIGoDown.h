#ifndef AIGODOWN_H
#define AIGODOWN_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "ManhattanDistance.h"
#include "WaveManager.h"
/**
	\brief Componete IA que se move para baixo
	
	É essencialmente uma IA placeholder que é prova de conceito de implementação de IA por componente.
*/
class AIGoDown : public Component
{
	public:
		/**
			\brief Construtor
			\param speed Velocidade de movimento, cujo sentido é para baixo.
			
			Instancia o componente.
		*/
		AIGoDown(float speed, int dest, TileMap &tileMap, WaveManager &wManager, GameObject &associated);
//		AIGoDown::~AI AIGoDown(void);
		//AIGoDown(float speed, GameObject &associated);
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
		float speed;/**< Velocidade de movimento do GameObject com esse componente.*/
		int destTile;
		TileMap& tileMap;
		WaveManager &waveManager;
		GameObject &associated;
};

#endif // AIGODOWN_H
