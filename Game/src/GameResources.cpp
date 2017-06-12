#include <fstream>
#include <string.h>
#include "GameResources.h"
#include "stdio.h"

#define ENEMY_TYPE_MAX_STRING_SIZE (50)
#define WAVE_DATA_FILENAME_MAX_SIZE (50)
#define ENEMY_MAX_NAME_LENGHT (100)
#define ENEMY_MAX_SPRITE_NAME_LENGHT (100)

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

void GameResources::ReadWeightData(std::string file){
	FILE *filePtr= fopen(file.c_str(), "r");
	if(NULL == filePtr){
		Error("\tCould not open " << file);
	}
	std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > newEntry(new std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE>() );
	char readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE+1];
	readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE]= '\0';
	int enemyTypeIndex;
	while(1 == fscanf(filePtr, "---%"ENEMY_TYPE_MAX_STRING_SIZE"s\n", readEnemyType)){
		enemyTypeIndex= GetEnemyTypeFromString(readEnemyType);
		int tileType, tileWeight, numbersRead;
		while(2 == (numbersRead = fscanf(filePtr, " %d:%d\n", &tileType, &tileWeight) ) ){
			(*newEntry)[enemyTypeIndex][tileType]= tileWeight;
		}
		if(1 == numbersRead){//pequena checagem de erro
			Error("\tFile " << file << " have invalid format.");
		}
	}
	fclose(filePtr);
	weightDataMap[file]= newEntry;
}

void GameResources::ReadWaveData(std::string file){
	FILE *filePtr= fopen(file.c_str(), "r");
	if(NULL == filePtr){
		Error("\tCould not open " << file);
	}
	std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > newEntry(new std::pair<std::vector<WaveData>, std::vector<EnemyData> >() );

	char readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE+1];
	readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE]= '\0';

	char* enemyName[ENEMY_MAX_NAME_LENGHT+1];
	enemyName[ENEMY_MAX_NAME_LENGHT]= '\0';
	fscanf(filePtr, "--ENEMIES--\n");
	ASSERT2(0 == ferror(filePtr), "\tFile format invalid! Expecting \"--ENEMIES--\".");
	while(1== fscanf(filePtr, "\t%"ENEMY_MAX_NAME_LENGHT"s\n", enemyName) ){
		int enemyTypeIndex;
		ASSERT2(1 == fscanf(filePtr, "\t\t%"ENEMY_TYPE_MAX_STRING_SIZE"s\n", readEnemyType), "\tFile format invaled! Expecting a string");
		char spriteFileName[ENEMY_MAX_SPRITE_NAME_LENGHT+1];
		spriteFileName[ENEMY_MAX_SPRITE_NAME_LENGHT]= '\0';
		//para dicionar mais sprites necessita-se duplicar essas linhas
		ASSERT2(1 == fscanf(filePtr, "\t\t%"ENEMY_MAX_SPRITE_NAME_LENGHT"s\n", spriteFileName), "\tFile format invalid! Expecting a string with sprite file." );
		float spriteX, spriteY;
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &spriteX), "\tFile format invalid! Expecting a float.");
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &spriteY), "\tFile format invalid! Expecting a float.");
		newEntry->second.emplace_back((enemyName, enemyTypeIndex, scaleX, scaleY, spriteFileName));//vê se esse uso consegue instanciar a struct, caso contrário criar construtor
	}
	//agora é ler o waveData
	fscanf(filePtr, "--WAVES--\n");
	ASSERT2(0 == ferror(filePtr), "\tFile format invalid! Expecting \"--WAVES--\".");
	
}

EnemyType GetEnemyTypeFromString(std::string str){
	if(!strcmp("HOSTILE", readEnemyType) ){
		return EnemyType::HOSTILE;
	}
	else if(!strcmp("NEUTRAL", readEnemyType) ){
		return EnemyType::NEUTRAL;
	}
	else if(!strcmp("ENGINEER", readEnemyType) ){
		return EnemyType::ENGINEER;
	}
	else if(!strcmp("ARQUITET", readEnemyType) ){
		return EnemyType::ARQUITET;
	}
	else if(!strcmp("ART", readEnemyType) ){
		return EnemyType::ART;
	}
	else if(!strcmp("QUIMIC", readEnemyType) ){
		return EnemyType::QUIMIC;
	}
	else{
		Error("\tTipo de inimigo não identificado " << readEnemyType << " durante a leitura do arquivo " << file);
	}
}
//void GameResources::SaveWeightData(std::array<std::map<int, int> *data)

//void GameResources::SaveWaveData(voidstd::pair<std::vector<WaveData>, std::vector<EnemyData> > *data);

