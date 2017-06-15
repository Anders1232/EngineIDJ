#ifndef WAVEDATA_H
#define WAVEDATA_H

#include <string>
#include <vector>
#include "Error.h"


struct EnemyData{
		//todo: ver como colocar cores e transparência aqui
	public:
		EnemyData(std::string name, int enemyType, float scaleX, float scaleY, std::string spName):
			name(name),
			enemyType(enemyType),
			scaleX(scaleX),
			scaleY(scaleY),
			spName(spName){}
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

		EnemySpawnData(int index, int numberOfEnemies, int baseHP, uint endPoint):
			enemyIndex(index),
			numberOfEnemies(numberOfEnemies),
			baseHP(baseHP),
			endPoint(endPoint){}
		int enemyIndex;
		uint numberOfEnemies;
		uint baseHP;
		uint endPoint;
};

struct SpawnPointData{
	public:
		std::vector<EnemySpawnData> enemySpawnData;
};

struct WaveData{
	public:
//		WaveData();
		std::string waveName;
		std::vector<SpawnPointData> spawnPointsData;
		
};

#endif // WAVEDATA_H
