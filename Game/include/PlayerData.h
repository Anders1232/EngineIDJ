
#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "GameObject.h"
#include "WaveManager.h"
#include "UItext.h"
#include "UItextButton.h"
#include "UIcanvas.h"
#include "UIverticalGroup.h"

#define TOTAL_LIFES 30;
class PlayerData: public Component{
	public:
		PlayerData();
		~PlayerData();
		void Render() const;
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const;
		void NotifyKillsUpdate(int wave, EnemyData enemyData);
		void NotifyLifeLost(int wave, EnemyData enemyData);
		void GoldUpdate(int amount);
		void PointsUpdate(int amount);

	private:
		UIcanvas HUDcanvas;
		UIverticalGroup playerTable;
		UItext boardName;
		UItext playerPoints;
		UItext playerGold;
		UItext playerKills;
		UItext playerLifes;


		int gold;
		uint kills;
		int lifes;
		int points;
		//WaveManager waveManager;	

};


#endif