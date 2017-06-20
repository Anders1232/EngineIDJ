#include "WaveManager.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Enemy.h"
#include "GameResources.h"
#include "Error.h"

#define TIME_BETWEEN_SPAWN (2.)

int WaveManager::waveCount = 0;

WaveManager::WaveManager(TileMap& tileMap, string waveFile): tileMap(tileMap) {
	endWave=false;
	enemiesLeft = 0;
	playerLifes = 30;
	spawnGroups= tileMap.GetSpawnPositions();
	wavesAndEnemysData = GameResources::GetWaveData("assets/wave&enemyData.txt");
	enemyIndex = 0;
	waveIndex=0;
	totalWaves = wavesAndEnemysData->first.size();
	StartWave();

}

WaveManager::~WaveManager(){
	//wavesAndEnemysData.clear();
	delete spawnGroups;
}

void WaveManager::StartWave(void){
	enemiesLeft=0;
	printf("Wave Start\n");
	for (uint i = 0; i < wavesAndEnemysData->first[waveIndex].spawnPointsData.size(); i++){
		for (uint j = 0; j < wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData.size(); j++){
			enemiesLeft += wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData[j].numberOfEnemies;
		}
	}
	//printf("\n %d enemiesLeft!!\n", enemiesLeft);
	waveTotalEnemies = enemiesLeft;
	enemyIndex = 0;
	endWave = false;
	++waveCount;
}


bool WaveManager::EndWave(void) const{
	return endWave;
}
 
void WaveManager::Update(GameObject &associated, float dt){
	int enemyId;
	WaveData currentWave = wavesAndEnemysData->first[waveIndex];
	//printf("\nwaveIndex:%d enemiesLeft:%d playerLifes:%d time:%.2f " , waveIndex, enemiesLeft, playerLifes, spawnTimer.Get());

	if(EndWave()){
		if(totalWaves==waveCount){ //Check Game over Condition
			return;
		}else{
			++waveIndex;
			StartWave();
		}
	}else{
		if(enemyIndex < waveTotalEnemies){ //check if spawned all enemies from current wave
			spawnTimer.Update(dt);
			if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){ // spawn cooldown
				//spawn 1 enemy at each existing spawn group
				for (uint i = 0; i < currentWave.spawnPointsData.size() and enemyIndex < waveTotalEnemies; i++){ 
					enemyId = currentWave.spawnPointsData[i].enemySpawnData[enemyIndex].enemyIndex;//here
					uint baseHP = currentWave.spawnPointsData[i].enemySpawnData[enemyIndex].baseHP;
					uint endPoint = currentWave.spawnPointsData[i].enemySpawnData[enemyIndex].endPoint;
					int spawnPosition = rand()% ( (*spawnGroups)[i] ).size();
					SpawnEnemy( (*spawnGroups)[i][spawnPosition], enemyId, baseHP, endPoint );
				}
				spawnTimer.Restart();
			}
		}
	}
	if (0 >= enemiesLeft){
		LoadNextAssets();
		endWave = true;
	}
}

void WaveManager::SpawnEnemy(int tileMapPosition, int enemyId, uint baseHP, uint endPoint ){
	EnemyData currentWaveEnemyData = wavesAndEnemysData->second[waveIndex];
	WaveData currentWave = wavesAndEnemysData->first[waveIndex];

	Vec2 tileSize= tileMap.GetTileSize();
	Vec2 spawnPosition;
	spawnPosition.x = (tileMapPosition%tileMap.GetWidth() ) * tileSize.x;
	spawnPosition.y = (tileMapPosition/tileMap.GetWidth() ) * tileSize.y;
	Enemy* enemy = new Enemy(spawnPosition, 1.);
	Game::GetInstance().GetCurrentState().AddObject(enemy);
	enemyIndex++;
	//printf("\n%d enemies spawned!",enemyIndex+1);

}



bool WaveManager::Is(ComponentType type) const{
	return type == WAVE_MANAGER;
}


void WaveManager::NotifyEnemyGotToHisDestiny(void){
	--playerLifes;

}
void WaveManager::NotifyEnemyGotKilled(void){
	--enemiesLeft;
}

int WaveManager::GetLifesLeft(void){
	return playerLifes;
}
int WaveManager::GetEnemiesLeft(void){
	return enemiesLeft;
}

void WaveManager::LoadNextAssets(void){
	// Resources::GetImage();
	// Resources::GetFont();
	// Resources::GetMusic();
	// Resources::GetSound();
}