#include "WaveManager.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Enemy.h"
#include "GameResources.h"
#include "Error.h"

#define TIME_BETWEEN_SPAWN (0.8)

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

void WaveManager::StartWave(){
	enemiesLeft=0;
	maxNumberOfEnemiesInSpawnPoint=0;
	int numberOfEnemiesInSpawnPoint;
	printf("Wave Start\n");
	for (uint i = 0; i < wavesAndEnemysData->first[waveIndex].spawnPointsData.size(); i++){
		numberOfEnemiesInSpawnPoint=0;
		for (uint j = 0; j < wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData.size(); j++){
			enemiesLeft += wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData[j].numberOfEnemies;
			numberOfEnemiesInSpawnPoint+= wavesAndEnemysData->first[waveIndex].spawnPointsData[i].enemySpawnData[j].numberOfEnemies;
		}
		if(numberOfEnemiesInSpawnPoint > maxNumberOfEnemiesInSpawnPoint){
			maxNumberOfEnemiesInSpawnPoint= numberOfEnemiesInSpawnPoint;
		}
	}
	//printf("\n %d enemiesLeft!!\n", enemiesLeft);
	waveTotalEnemies = enemiesLeft;
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
	//printf("\nwaveIndex:%d enemiesLeft:%d playerLifes:%d time:%.2f " , waveIndex, enemiesLeft, playerLifes, spawnTimer.Get());

	if(EndWave()){
		if(totalWaves==waveCount){ //Check Game over Condition
			//Ao invés de não fazer nada deve-ser informar o fim de jogo
			return;
		}else{
			++waveIndex;
			StartWave();
		}
	}else{
		spawnTimer.Update(dt);
		if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){ // spawn cooldown
			//spawn 1 enemy at each existing spawn group
			for (uint i = 0; i < currentWave.spawnPointsData.size(); i++){
				if()
				EnemySpawnData &enemyToSpawn= currentWave.spawnPointsData[i].enemySpawnData[enemyIndex];
				REPORT_DEBUG2(1, "\t enemyIndex= " << enemyToSpawn.enemyIndex);
				REPORT_DEBUG2(1, "\t baseHP= " << enemyToSpawn.baseHP);
				REPORT_DEBUG2(1, "\t endPoint= " << enemyToSpawn.endPoint);
				int spawnPosition = rand()% ( (*spawnGroups)[i] ).size();
				SpawnEnemy( (*spawnGroups)[i][spawnPosition], enemyToSpawn.enemyIndex, enemyToSpawn.baseHP, enemyToSpawn.endPoint );
			}
			spawnTimer.Restart();
		}
	}
	if (0 >= enemiesLeft){
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


void WaveManager::NotifyEnemyGotToHisDestiny(){
	--playerLifes;

}
void WaveManager::NotifyEnemyGotKilled(){
	--enemiesLeft;
}

int WaveManager::GetLifesLeft(){
	return playerLifes;
}
int WaveManager::GetEnemiesLeft(){
	return enemiesLeft;
}

