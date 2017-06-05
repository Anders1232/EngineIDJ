#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"
#include "Timer.h"
#include "TileMap.h"
#include "Component.h"

using std::vector;

class WaveManager : public Component {
	public:
		WaveManager(TileMap& tileMap, string waveFile);
		~WaveManager();
		
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const;
		bool EndWave();
	private:
		void SpawnEnemy(int tileMapPosition);
		vector<vector<int>> *spawnGroups;
		static int waveCount; //contador de waves restantes. Tbm usado para nivelar as waves
		Timer spawnTimer;
		int enemiesLeft;
		TileMap &tileMap;
		bool endWave; //true se a level acabou
};

#endif