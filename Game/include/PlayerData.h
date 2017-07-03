
#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "WaveManager.h"
#include "UItext.h"
#include "UItextButton.h"


#define TOTAL_LIFES 30;
class PlayerData: public Component{
	public:
		PlayerData();
		~PlayerData();
		void Render() const;
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const;
		void NotifyGoldUpdate(int amount);
		void NotifyKillsUpdate();
		void NotifyLifesUpdate();
	private:
		UItext name;
		int gold;
		uint kills;
		int lifes;
		//WaveManager waveManager;	

};


#endif