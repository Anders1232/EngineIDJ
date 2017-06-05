#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"
#include "Timer.h"
#include "TileMap.h"

using std::vector;

class Wave
{
public:
	Wave(TileMap *tileMap);
	~Wave();
	
	void Update(float dt);
	void SpawnEnemy(int tileMapPosition);
	bool EndWave();

	vector<vector<int>> *spawnGroups;
	static int waveCount; //contador de waves restantes. Tbm usado para nivelar as waves
	Timer spawnTimer;
	int enemiesLeft;
	//TileMap tileMap;
	bool endWave; //true se a level acabou
};

#endif