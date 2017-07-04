#ifndef AISHOOTERTOWER_H
#define AISHOOTERTOWER_H

#include "Component.h"
#include "TileMap.h"
#include "GameResources.h"
#include "Bullet.h"
#include "Timer.h"
#include "Game.h"

#define TOWER_MAX_BULLET_COOLDOWN 1

/**
	\brief Componete IA que atira em inimigos
*/
class AIShooterTower : public Component
{
	public:
		/**
			Instancia o componente.
		*/
		AIShooterTower(GameObject& associated,TileMap& tileMap,std::string bullet);
		/**
			\brief Atualiza estado.
			\param dt Intervalo de tempo desde a última chamada.
		*/
		void Update(float dt);
		/**
			\brief Verifica se essa componente é do tipo informado.
			
			Método herdade do componente com o objetivo de identificar que tipo de componente é.
		*/
		bool Is(std::string type) const;

	private:
		Timer bulletsCoolDown;
		TileMap& tileMap;
		GameObject& associated;
		std::string bulletSp;
};

#endif 