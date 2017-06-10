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
	enemyIndex = 0;
	waveIndex=0;
	totalWaves = wavesAndEnemysData->first.size();
	StartWave();

}

WaveManager::~WaveManager(){
	delete spawnGroups;
	//delete wavesAndEnemysData;
}

void WaveManager::StartWave(){
	enemiesLeft=0;
	for (uint i = 0; i < wavesAndEnemysData->first[waveIndex].spawnPointsData.size(); i++){
		for (uint j = 0; j < wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData.size(); j++){
			enemiesLeft += wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData[j].quant;
		}
	}
	
	enemyIndex = 0;
	endWave = false;
	++waveCount;
}


bool WaveManager::EndWave(){
	return endWave;
}

void WaveManager::Update(GameObject &associated, float dt){
	int enemyId;
	WaveData currentWave = wavesAndEnemysData->first[waveIndex];
	EnemyData currentWaveEnemy = wavesAndEnemysData->second[waveIndex];
	
	if(EndWave()){
		if(totalWaves==waveCount){ //Game end Condition
			return;
		}else{
			++waveIndex;
			StartWave();
		}
	}else {
		/*
		spawnTimer.Update(dt);
		if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){
			int selectedSpawnGroup = rand()%spawnGroups->size();
			int selectedSpawnPosition = rand()% ( (*spawnGroups)[selectedSpawnGroup] ).size();
			SpawnEnemy( (*spawnGroups)[selectedSpawnGroup][selectedSpawnPosition], 0 );
			spawnTimer.Restart();
		}*/
		//usando Resources
		spawnTimer.Update(dt);
		if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){
			for (uint i = 0; i < currentWave.spawnPointsData.size(); i++){
				enemyId = currentWave.spawnPointsData[i].enemySpawnData[enemyIndex].enemyIndex;
				int spawnPosition = rand()% currentWave.spawnPointsData[i].tiles.size();
				SpawnEnemy( (*spawnGroups)[i][spawnPosition], enemyId );
			}
			spawnTimer.Restart();
		}
	}
	if (0 >= enemiesLeft){
		endWave = true;
	}
}

void WaveManager::SpawnEnemy(int tileMapPosition, int enemyId){
	Vec2 tileSize= tileMap.GetTileSize();
	Vec2 spawnPosition;
	spawnPosition.x = (tileMapPosition%tileMap.GetWidth() ) * tileSize.x;
	spawnPosition.y = (tileMapPosition/tileMap.GetWidth() ) * tileSize.y;
	Enemy* enemy = new Enemy(spawnPosition, 1.);
	//new Enemy(spawnPosition, enemyIndex, uint quant, uint baseHP, uint endPoint)
	Game::GetInstance().GetCurrentState().AddObject(enemy);
}


bool WaveManager::Is(ComponentType type) const{
	return type == WAVE_MANAGER;
}