#include <fstream>
#include <string.h>
#include "GameResources.h"
#include "stdio.h"

#include "Error.h"
#include <vector>

#define ENEMY_TYPE_MAX_STRING_SIZE (50)
#define WAVE_DATA_FILENAME_MAX_SIZE (50)
#define ENEMY_MAX_NAME_LENGHT (100)
#define ENEMY_MAX_SPRITE_NAME_LENGHT (100)
#define WAVE_NAME_MAX_LENGHT (100)



std::unordered_map<string, std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > > GameResources::weightDataMap;
std::unordered_map<string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > GameResources::waveDataMap;

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
	while(1 == fscanf(filePtr, "---%s\n", readEnemyType)){
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

	char enemyName[ENEMY_MAX_NAME_LENGHT+1];
	enemyName[ENEMY_MAX_NAME_LENGHT]= '\0';
	fscanf(filePtr, "--ENEMIES--\n");
	ASSERT2(0 == ferror(filePtr), "\tFile format invalid! Expecting \"--ENEMIES--\".");
	
	while( 1 == fscanf(filePtr, "\t%s\n", enemyName)){
		if (!strcmp("--WAVES--", enemyName)){
			break;
		}
		int enemyTypeIndex;
		
		ASSERT2(1 == fscanf(filePtr, "\t\t%s\n", readEnemyType), "\tFile format invalid! Expecting a string");
		enemyTypeIndex= GetEnemyTypeFromString(readEnemyType);
		char spritePath[ENEMY_MAX_SPRITE_NAME_LENGHT+1];
		spritePath[ENEMY_MAX_SPRITE_NAME_LENGHT]= '\0';
		//para dicionar mais sprites necessita-se duplicar essas linhas
		ASSERT2( (1 == fscanf(filePtr, "\t\t%s\n", spritePath) ), "\tFile format invalid! Expecting a string with sprite file." );
		float scaleX, scaleY;
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &scaleX), "\tScaleX File format invalid! Expecting a float.");
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &scaleY), "\tScaleY File format invalid! Expecting a float.");
		newEntry->second.emplace_back(enemyName, enemyTypeIndex, scaleX, scaleY, spritePath);//vê se esse uso consegue instanciar a struct, caso contrário criar construtor
	}
	char waveName[WAVE_NAME_MAX_LENGHT+1];
	waveName[WAVE_NAME_MAX_LENGHT]= '\0';
	vector<WaveData> &waveVec= newEntry->first;
	while(1== fscanf(filePtr, " %s\n", waveName) ){
		REPORT_DEBUG2(1, "\t waveName= " << waveName);
		//TEMP_REPORT_I_WAS_HERE;
		waveVec.emplace_back();

		waveVec[waveVec.size()-1].waveName = waveName;
		vector<SpawnPointData> &spawnPointsVec = waveVec[waveVec.size()-1].spawnPointsData;
		uint spawnPoint;
		ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
		while(1 == fscanf(filePtr, "\tSpawnPoint:%u\n", &spawnPoint)){
			if(spawnPointsVec.size() < spawnPoint+1){
				spawnPointsVec.resize(spawnPoint+1);
			}


			vector<EnemySpawnData> &enemySpawnVector = spawnPointsVec[spawnPoint].enemySpawnData;
			int enemyIndex;
			while(1 == fscanf(filePtr, "\t\t\t%d\n", &enemyIndex) ){
				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				int numberOfEnemies;
				ASSERT2(1 == fscanf(filePtr, "\t\t%d\n", &numberOfEnemies), "\tFile format invaled! Expecting a integer.");
				int enemyHP;
				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				ASSERT2(1 == fscanf(filePtr, "\t\t%d\n", &enemyHP), "\tFile format invaled! Expecting a integer.");
				uint endPoint;
				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				ASSERT2(1 == fscanf(filePtr, "\t\t%u\n", &endPoint), "\tFile format invaled! Expecting a integer.");
				REPORT_DEBUG( "\t enemyIndex= " << enemyIndex);
				REPORT_DEBUG( "\t numberOfEnemies= " << numberOfEnemies);
				REPORT_DEBUG( "\t enemyHP= " << enemyHP);
				REPORT_DEBUG( "\t endPoint= " << endPoint);
				if(ferror(filePtr)){
					break;
				}
				enemySpawnVector.emplace_back(enemyIndex, numberOfEnemies, enemyHP, endPoint);
			}
		}
	}
	fclose(filePtr);
	waveDataMap[file]= newEntry;
	
}

EnemyType GameResources::GetEnemyTypeFromString(std::string str){
	if("HOSTILE" == str){
		return EnemyType::HOSTILE;
	}
	else if("NEUTRAL" == str){
		return EnemyType::NEUTRAL;
	}
	else if("ENGINEER" == str){
		return EnemyType::ENGINEER;
	}
	else if("ARQUITET" == str){
		return EnemyType::ARQUITET;
	}
	else if("ART" == str){
		return EnemyType::ART;
	}
	else if("QUIMIC" == str){
		return EnemyType::QUIMIC;
	}
	else{
		Error("\tTipo de inimigo não identificado " << str);
	}
}

void GameResources::Clear(void){
	auto i= weightDataMap.begin();
	while(i != weightDataMap.end()) {
		if((*i).second.unique()) {
			i= weightDataMap.erase(i);
		}
		else {
			i++;
		}
	}
	
	auto j= waveDataMap.begin();
	while(j != waveDataMap.end()) {
		if((*j).second.unique()) {
			j= waveDataMap.erase(j);
		}
		else {
			j++;
		}
	}

}

//void GameResources::SaveWeightData(std::array<std::map<int, int> *data)

//void GameResources::SaveWaveData(voidstd::pair<std::vector<WaveData>, std::vector<EnemyData> > *data);
