#include <fstream>
#include <string.h>
#include "GameResources.h"
#include "stdio.h"

#define ENEMY_TYPE_MAX_STRING_SIZE 50

std::unordered_map<std::string, std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > > GameResources::weightDataMap;
std::unordered_map<std::string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > GameResources::waveDataMap;

std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > GameResources::GetWeightData(std::string file){
	if(weightDataMap.end() == weightDataMap.find(file)) {
		ReadWaveData(file);
	}
	return weightDataMap[file];
}

std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > GameResources::GetWaveData(std::string file){
	if(waveDataMap.end() == waveDataMap.find(file)) {
		ReadWaveData(file);
	}
	return waveDataMap[file];
}

void GameResources::ReadWaveData(std::string file){
	FILE *filePtr= fopen(file.c_str(), "r");
	std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > newEntry(new std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE>() );
	char readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE+1];
	readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE]= '\0';
	int enemyTypeIndex;
	while(1 == fscanf(filePtr, "---%s\n", readEnemyType)){
		if(!strcmp("HOSTILE", readEnemyType) ){
			enemyTypeIndex= EnemyType::HOSTILE;
		}
		else if(!strcmp("NEUTRAL", readEnemyType) ){
			enemyTypeIndex= EnemyType::NEUTRAL;
		}
		else if(!strcmp("ENGINEER", readEnemyType) ){
			enemyTypeIndex= EnemyType::ENGINEER;
		}
		else if(!strcmp("ARQUITET", readEnemyType) ){
			enemyTypeIndex= EnemyType::ARQUITET;
		}
		else if(!strcmp("ART", readEnemyType) ){
			enemyTypeIndex= EnemyType::ART;
		}
		else if(!strcmp("QUIMIC", readEnemyType) ){
			enemyTypeIndex= EnemyType::QUIMIC;
		}
		else{
			Error("\tTipo de inimigo não identificado " << readEnemyType << " durante a leitura do arquivo " << file);
		}
		int tileType, tileWeight, numbersRead;
		while(2 == (numbersRead = fscanf(filePtr, " %d:%d\n", &tileType, &tileWeight) ) ){
			(*newEntry)[enemyTypeIndex][tileType]= tileWeight;
		}
		if(1 == numbersRead || 2 < numbersRead){//pequena checagem de erro
			Error("\tFile " << file << " have invalid format.");
		}
	}
}

//void GameResources::ReadWeightData(std::string file);

//void GameResources::SaveWeightData(std::array<std::map<int, int> *data)

//void GameResources::SaveWaveData(voidstd::pair<std::vector<WaveData>, std::vector<EnemyData> > *data);

