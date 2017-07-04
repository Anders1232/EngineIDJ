#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "Game.h"
#include "GameResources.h"
#include "Error.h"

#define ENEMY_TYPE_MAX_STRING_SIZE (50)
#define WAVE_DATA_FILENAME_MAX_SIZE (50)
#define ENEMY_MAX_NAME_LENGHT (100)
#define ENEMY_MAX_SPRITE_NAME_LENGHT (100)
#define WAVE_NAME_MAX_LENGHT (100)

std::unordered_map<std::string, std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > > GameResources::weightDataMap;
std::unordered_map<std::string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > GameResources::waveDataMap;
std::unordered_map<std::string, std::pair<uint, std::shared_ptr<std::vector<int> > > > GameResources::pathMap;
uint GameResources::lastMapUpdate=0;
TileMap* GameResources::tileMap= nullptr;

std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > GameResources::GetWeightData(std::string file){
	if(weightDataMap.end() == weightDataMap.find(file)) {
		ReadWeightData(file);
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
	std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > newEntry(new std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE>() );
	char readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE+1];
	readEnemyType[ENEMY_TYPE_MAX_STRING_SIZE]= '\0';
	int enemyTypeIndex;
	while(1 == fscanf(filePtr, "---%s\n", readEnemyType)){
		enemyTypeIndex= GetEnemyTypeFromString(readEnemyType);
		int tileType, numbersRead;
		double tileWeight;
		while(2 == (numbersRead = fscanf(filePtr, " %d:%lf\n", &tileType, &tileWeight) ) ){
			(*newEntry)[enemyTypeIndex][tileType]= tileWeight;
		}
		if(1 == numbersRead){//pequena checagem de erro
			Error("\tFile " << file << " have invalid format.");
		}
		fseek (filePtr,-1,SEEK_CUR);
	}
	fclose(filePtr);
	weightDataMap[file] = newEntry;
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
		REPORT_DEBUG("\t waveName= " << waveName);
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
	else if("MEDIC" == str){
		return EnemyType::MEDIC;
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

void GameResources::SetTileMap(TileMap *map){
	tileMap= map;
}

void GameResources::NotifyTileMapChanged(void){
	lastMapUpdate= Game::GetInstance().GetTicks();
}

std::string GameResources::GetEnemyTypeStringFromType(EnemyType type){
	if(EnemyType::HOSTILE == type){
		return "HOSTILE";
	}
	else if(EnemyType::NEUTRAL == type){
		return "NEUTRAL";
	}
	else if(EnemyType::ENGINEER == type){
		return "ENGINEER";
	}
	else if(EnemyType::ARQUITET == type){
		return "ARQUITET";
	}
	else if(EnemyType::ART == type){
		return "ART";
	}
	else if(EnemyType::QUIMIC == type){
		return "QUIMIC";
	}
	else if(EnemyType::MEDIC == type){
		return "MEDIC";
	}
	else{
		Error("\tTipo de inimigo não identificado " << type);
	}
}


std::shared_ptr<std::vector<int> > GameResources::GetPath(EnemyType type, AStarHeuristic *heuristic, int origin, int dest, std::string weightDataFile){
	std::string index= std::to_string(origin);
	index += GetEnemyTypeStringFromType(type);
	index += std::to_string(dest);
	try{
		if(pathMap.at(index).first == lastMapUpdate){
			return pathMap[index].second;
		}
	}
	catch(...){
		pathMap.erase(index);
	}
	std::map<int, double> weightMap= GetWeightData(weightDataFile)->operator [](type);
	std::list<int>*pathList= tileMap->AStar(origin, dest, heuristic, weightMap);
	std::vector<int> *pathVector= new std::vector<int>(pathList->begin(), pathList->end());
	delete pathList;
	std::shared_ptr<std::vector<int>> newPath(pathVector);
	std::pair<uint, std::shared_ptr<std::vector<int> > > newEntry= std::make_pair(lastMapUpdate, newPath);
	pathMap[index]= newEntry;
	return newPath;
}


