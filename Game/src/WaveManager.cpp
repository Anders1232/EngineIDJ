#include "WaveManager.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Enemy.h"

#define TIME_BETWEEN_SPAWN (3.)

int WaveManager::waveCount = 0;

WaveManager::WaveManager(TileMap& tileMap, string waveFile): tileMap(tileMap) {
	endWave=false;
	enemiesLeft = 0;
	spawnGroups= tileMap.GetSpawnPositions();
	wavesAndEnemysData = GameResources::GetWaveData();

	waveIndex=0;
	totalWaves = wavesAndEnemysData->first.size();
	StartWave();

}

WaveManager::~WaveManager(){
	delete spawnGroups;

}

void WaveManager::StartWave(){
	enemiesLeft=0;
	for (uint i = 0; i < wavesAndEnemysData->first[waveIndex].spawnPointsData.size(); ++i){
		for (uint j = 0; j < wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData.size(); ++i){
			enemiesLeft += wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData[j].quant;
		}
	}
	

	endWave = false;
	++waveCount;
}

bool WaveManager::EndWave(){
	if (0 >= enemiesLeft){
		return true;
	}
	else{
		return false;
	}
}

void WaveManager::Update(GameObject &associated, float dt){
	
	
	if(EndWave()){
		if(totalWaves==waveCount){ //Game end Condition
			return;
		}else{
			++waveIndex;
			StartWave();
		}
	}else {

		spawnTimer.Update(dt);
		if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){
			int selectedSpawnGroup = rand()%spawnGroups->size();
			int selectedSpawnPosition = rand()% ( (*spawnGroups)[selectedSpawnGroup] ).size();
			SpawnEnemy( (*spawnGroups)[selectedSpawnGroup][selectedSpawnPosition] );
			spawnTimer.Restart();
		}
	}

}

void WaveManager::SpawnEnemy(int tileMapPosition){
	Vec2 tileSize= tileMap.GetTileSize();
	Vec2 spawnPosition;
	spawnPosition.x = (tileMapPosition%tileMap.GetWidth() ) * tileSize.x;
	spawnPosition.y = (tileMapPosition/tileMap.GetWidth() ) * tileSize.y;
	Enemy* enemy = new Enemy(spawnPosition, 1.);
	Game::GetInstance().GetCurrentState().AddObject(enemy);
}


bool WaveManager::Is(ComponentType type) const{
	return type == WAVE_MANAGER;
}