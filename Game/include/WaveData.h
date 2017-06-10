#ifndef WAVEDATA_H
#define WAVEDATA_H

#include <string>
#include <vector>
#include "Error.h"

typedef unsigned int uint;

struct EnemyData{
		//todo: ver coo colocar cores e transparência aqui
	public:
		std::string name;
		float scaleX;
		float sacleY;
		std::string bodySpName;
		std::string headSpName;
		std::string pantsSpName;
};

struct EnemySpawnData{
	public:
		int enemyIndex;
		uint quant;
		uint baseHP;
		uint endPoint;
};

struct SpawnPointData{
	public:
		std::vector<EnemySpawnData> enemySpawnData;
};

struct WaveData{
	public:
		WaveData();
		
		std::vector<SpawnPointData> spawnPointsData;
		
};

#endif // WAVEDATA_H
