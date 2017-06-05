#include "Wave.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Enemy.h"

#define TIME_BETWEEN_SPAWN (3.)
int Wave::waveCount = 0;

Wave::Wave(TileMap* tileMap){
	waveCount++;
	endWave=false;
	enemiesLeft = 0;
	spawnGroups= tileMap->GetSpawnPositions();
}

Wave::~Wave(){
	delete spawnGroups;
}

void Wave::Update(float dt){
	spawnTimer.Update(dt);
	if(TIME_BETWEEN_SPAWN < spawnTimer.Get()){
		int selectedSpawnGroup = rand()%spawnGroups->size();
		int selectedSpawnPosition = rand()% ( (*spawnGroups)[selectedSpawnGroup] ).size();
		SpawnEnemy( (*spawnGroups)[selectedSpawnGroup][selectedSpawnPosition]);
		spawnTimer.Restart();
	}

}

void Wave::SpawnEnemy(int tileMapPosition, TileMap* tileMap){
	Vec2 tileSize= tileMap->GetTileSize();
	Vec2 spawnPosition;
	spawnPosition.x= (tileMapPosition%tileMap->GetWidth() ) * tileSize.x;
	spawnPosition.y= (tileMapPosition/tileMap->GetWidth() ) * tileSize.y;
	Enemy* enemy = new Enemy(spawnPosition, 1.);
	Game::GetInstance().GetCurrentState().AddObject(enemy);
}


bool Wave::EndWave(){
	if (enemiesLeft <= 0)
		return true;
	else
		return false;
}