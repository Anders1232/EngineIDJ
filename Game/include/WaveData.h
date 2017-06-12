#ifndef WAVEDATA_H
#define WAVEDATA_H

#include <string>
#include <vector>
#include "Error.h"

struct EnemyData{
		//todo: ver coo colocar cores e transparência aqui
	public:
		std::string name;
		int enemyType;
		float scaleX;
		float scaleY;
		std::string spName;
//		std::string headSpName;
//		std::string pantsSpName;
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
