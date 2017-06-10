#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"
#include "Timer.h"
#include "TileMap.h"
#include "Component.h"
#include "WaveData.h"

#include <memory>
//#include "EnemyData.h"

using std::vector;

class WaveManager : public Component {
	public:
		WaveManager(TileMap& tileMap, string waveFile);
		~WaveManager();
		
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const;
		void StartWave();
		bool EndWave();
	private:
		void SpawnEnemy(int tileMapPosition, int enemyId);
		vector<vector<int>> *spawnGroups;
		static int waveCount; //contador de waves restantes. Tbm usado para nivelar as waves
		Timer spawnTimer;
		int enemiesLeft;
		TileMap &tileMap;
		bool endWave; //true se a level acabou
		std::shared_ptr< std::pair< std::vector<WaveData>, std::vector<EnemyData> > > wavesAndEnemysData;
		int waveIndex, enemyIndex, totalWaves;

};

#endif

//sprite dos inimigos, escala, nome, vida_base,
/*
std::pair<std::shared_ptr<std::vector<WaveData>>, std::shared_ptr<std::vector<EnemyData>> >
pair<shared_ptr<vector<WaveData>>, shared_ptr<vector<enemyData>> >
*/