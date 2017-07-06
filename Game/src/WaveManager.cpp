#include "WaveManager.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Enemy.h"
#include "GameResources.h"
#include "Error.h"
#include "PlayerData.h"

#define TIME_BETWEEN_SPAWN (0.8)
#define TIME_BETWEEN_WAVE (5.0)
int WaveManager::waveCount = 0;


WaveManager::WaveManager(TileMap& tileMap, string waveFile): tileMap(tileMap) {
	endWave=false;
	enemiesLeft = 0;
	REPORT_DEBUG2(1, "Buscando spawn points.");
	spawnGroups= tileMap.GetTileGroups(SPAWN_POINT);
	REPORT_DEBUG2(1, "Buscando end points.");
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
	printf("Wave %d Start!", waveCount);

}


bool WaveManager::EndWave(){
	return endWave;
}

void WaveManager::Update(float dt){
	WaveData currentWave = wavesAndEnemysData->first[waveIndex];

	if(EndWave()){

		if(totalWaves==waveCount){ //Check Game over Condition
			victory = true;
			return;
		}else{

            waveTimer.Update(dt);
            if(TIME_BETWEEN_WAVE < waveTimer.Get()) {
				++waveIndex;
				StartWave();

			}else{
				//waiting for next wave...
				printf("Next wave start in %f\n", waveTimer.Get());
			}
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
					while(enemiesCounter >= currentWave.spawnPointsData.at(i).enemySpawnData.at(indexOfTheEnemyToSpawn).numberOfEnemies){
						if(indexOfTheEnemyToSpawn>= currentWave.spawnPointsData.at(i).enemySpawnData.size()){
							breaked= true;
							break;
						}
						enemiesCounter-= currentWave.spawnPointsData.at(i).enemySpawnData.at(indexOfTheEnemyToSpawn).numberOfEnemies;
						indexOfTheEnemyToSpawn++;
						if(indexOfTheEnemyToSpawn>= currentWave.spawnPointsData.at(i).enemySpawnData.size()){
							breaked= true;
							break;
						}
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
					int endPosition= rand()% ( ( (*endGroups).at(enemyToSpawn.endPoint) ).size());
					int endTilePosition= (*endGroups).at(enemyToSpawn.endPoint).at(endPosition);
					SpawnEnemy( (*spawnGroups).at(i).at(spawnPosition), enemyToSpawn.enemyIndex, enemyToSpawn.baseHP, endTilePosition, indexOfTheEnemyToSpawn );
				}
				spawnTimer.Restart();
				enemyIndex++;
			}
		}

        if (0 >= enemiesLeft){
            endWave = true;
            waveTimer.Restart();
            //bounty level complete
            float income = (waveCount* 5)+100;
            PlayerData::GetInstance().GoldUpdate((int)income);
        }
	}

}

void WaveManager::SpawnEnemy(int tileMapPosition, int enemyId, uint baseHP, uint endPoint, uint indexOfTheEnemyToSpawn ){
	EnemyData &currentWaveEnemyData = wavesAndEnemysData->second[indexOfTheEnemyToSpawn];
	REPORT_DEBUG("\t currentWaveEnemyData.scale= ("<<currentWaveEnemyData.scaleX<<","<<currentWaveEnemyData.scaleY<<")" );
	Vec2 tileSize= tileMap.GetTileSize();
	Vec2 spawnPosition;
	REPORT_I_WAS_HERE;
	spawnPosition.x = (tileMapPosition%tileMap.GetWidth() ) * tileSize.x;
	REPORT_I_WAS_HERE;
	spawnPosition.y = (tileMapPosition/tileMap.GetWidth() ) * tileSize.y;
	Enemy* enemy = new Enemy(spawnPosition, enemyIndex, currentWaveEnemyData, baseHP, endPoint, tileMap, *this);
	Game::GetInstance().GetCurrentState().AddObject(enemy);
}

bool WaveManager::Is(ComponentType type) const{
	return type == WAVE_MANAGER;
}

void WaveManager::NotifyEnemyGotToHisDestiny(){
	PlayerData::GetInstance().DecrementLife();
	--enemiesLeft;
}

void WaveManager::NotifyEnemyGotKilled(){
	--enemiesLeft;
}

int WaveManager::GetEnemiesLeft(){
	return enemiesLeft;
}

bool WaveManager::Victory(){
	return victory;
}
