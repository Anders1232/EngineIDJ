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
	spawnGroups= tileMap.GetTileGroups(SPAWN_POINT);
	endGroups= tileMap.GetTileGroups(END_POINT);
	wavesAndEnemysData = GameResources::GetWaveData("assets/wave&enemyData.txt");
	enemyIndex = 0;
	waveIndex=0;
	totalWaves = wavesAndEnemysData->first.size();
	victory = false;
	StartWave();
}

WaveManager::~WaveManager(){
	delete spawnGroups;
	delete endGroups;
}

void WaveManager::StartWave(){
	enemiesLeft=0;
	maxNumberOfEnemiesInSpawnPoint=0;
	int numberOfEnemiesInSpawnPoint;
	REPORT_I_WAS_HERE;
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
	waveTotalEnemies = enemiesLeft;
	enemyIndex = 0;
	endWave = false;
	++waveCount;

}


bool WaveManager::EndWave(){
	return endWave;
}
 
void WaveManager::Update(GameObject &associated, float dt){
	WaveData currentWave = wavesAndEnemysData->first[waveIndex];

	if(EndWave()){
		if(totalWaves==waveCount){ //Check Game over Condition
			//Ao invés de não fazer nada deve-ser informar o fim de jogo
			victory = true;
			return;
		}else{
			REPORT_I_WAS_HERE;
			++waveIndex;
			StartWave();
		}
	}else{
		if(enemyIndex <= maxNumberOfEnemiesInSpawnPoint){
			spawnTimer.Update(dt);
			if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){ // spawn cooldown
				//spawn 1 enemy at each existing spawn group

				for (uint i = 0; i < currentWave.spawnPointsData.size(); i++){
					uint enemiesCounter= enemyIndex;
					uint indexOfTheEnemyToSpawn=0;
					bool breaked= false;
					REPORT_I_WAS_HERE;
					while(enemiesCounter >= currentWave.spawnPointsData.at(i).enemySpawnData.at(indexOfTheEnemyToSpawn).numberOfEnemies){
						REPORT_I_WAS_HERE;
						if(indexOfTheEnemyToSpawn>= currentWave.spawnPointsData.at(i).enemySpawnData.size()){
							REPORT_I_WAS_HERE;
							breaked= true;
							REPORT_I_WAS_HERE;
							break;
						}
						REPORT_I_WAS_HERE;
						enemiesCounter-= currentWave.spawnPointsData.at(i).enemySpawnData.at(indexOfTheEnemyToSpawn).numberOfEnemies;
						indexOfTheEnemyToSpawn++;
						REPORT_I_WAS_HERE;
						if(indexOfTheEnemyToSpawn>= currentWave.spawnPointsData.at(i).enemySpawnData.size()){
							REPORT_I_WAS_HERE;
							breaked= true;
							REPORT_I_WAS_HERE;
							break;
						}
						REPORT_I_WAS_HERE;
					}
					if(breaked){
						continue;
					}
					REPORT_DEBUG("\t indexOfTheEnemyToSpawn= " << indexOfTheEnemyToSpawn);
					
					EnemySpawnData &enemyToSpawn= currentWave.spawnPointsData.at(i).enemySpawnData.at(indexOfTheEnemyToSpawn);
					REPORT_DEBUG("\t enemyIndex= " << enemyToSpawn.enemyIndex);
					REPORT_DEBUG("\t baseHP= " << enemyToSpawn.baseHP);
					REPORT_DEBUG("\t endPoint= " << enemyToSpawn.endPoint);
					int spawnPosition = rand()% ( (*spawnGroups).at(i) ).size();
					TEMP_REPORT_I_WAS_HERE;
					int endPosition= rand()% ( ( (*endGroups).at(enemyToSpawn.endPoint) ).size());
					TEMP_REPORT_I_WAS_HERE;
					int endTilePosition= (*endGroups).at(enemyToSpawn.endPoint).at(endPosition);

					TEMP_REPORT_I_WAS_HERE;
					SpawnEnemy( (*spawnGroups).at(i).at(spawnPosition), enemyToSpawn.enemyIndex, enemyToSpawn.baseHP, endTilePosition, indexOfTheEnemyToSpawn );
					TEMP_REPORT_I_WAS_HERE;
				}
				REPORT_I_WAS_HERE;
				spawnTimer.Restart();

				enemyIndex++;
			}
			REPORT_I_WAS_HERE;
		}
		REPORT_I_WAS_HERE;
	}
	REPORT_I_WAS_HERE;
	if (0 >= enemiesLeft){
		endWave = true;
	}
}

void WaveManager::SpawnEnemy(int tileMapPosition, int enemyId, uint baseHP, uint endPoint, uint indexOfTheEnemyToSpawn ){
	EnemyData &currentWaveEnemyData = wavesAndEnemysData->second[indexOfTheEnemyToSpawn];
	TEMP_REPORT_I_WAS_HERE;
	REPORT_DEBUG("\t currentWaveEnemyData.scale= ("<<currentWaveEnemyData.scaleX<<","<<currentWaveEnemyData.scaleY<<")" );
	TEMP_REPORT_I_WAS_HERE;
	Vec2 tileSize= tileMap.GetTileSize();
	TEMP_REPORT_I_WAS_HERE;
	Vec2 spawnPosition;
	REPORT_I_WAS_HERE;
	spawnPosition.x = (tileMapPosition%tileMap.GetWidth() ) * tileSize.x;
	REPORT_I_WAS_HERE;
	spawnPosition.y = (tileMapPosition/tileMap.GetWidth() ) * tileSize.y;
	TEMP_REPORT_I_WAS_HERE;
	Enemy* enemy = new Enemy(spawnPosition, enemyIndex, currentWaveEnemyData, baseHP, endPoint, tileMap);
	TEMP_REPORT_I_WAS_HERE;
	Game::GetInstance().GetCurrentState().AddObject(enemy);
	TEMP_REPORT_I_WAS_HERE;
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
bool WaveManager::Victory(){
	return victory;

}
