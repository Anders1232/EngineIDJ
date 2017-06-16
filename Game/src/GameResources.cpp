#include <fstream>
#include <string.h>
#include "GameResources.h"
#include "stdio.h"
#include "Error.h"

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
	
	while( true ){
		fscanf(filePtr, "\t%s\n", enemyName);
		string name = enemyName;
		if (name.compare("--WAVES--") != 0){
			break;
		}
		int enemyTypeIndex;
		
		printf("\nenemyName:%s\n", enemyName);
		
		ASSERT2(1 == fscanf(filePtr, "\t\t%s\n", readEnemyType), "\tFile format invalid! Expecting a string");
		char spriteFileName[ENEMY_MAX_SPRITE_NAME_LENGHT+1];
		spriteFileName[ENEMY_MAX_SPRITE_NAME_LENGHT]= '\0';
		//para dicionar mais sprites necessita-se duplicar essas linhas
		ASSERT2( (1 == fscanf(filePtr, "\t\t%s\n", spriteFileName) ), "\tFile format invalid! Expecting a string with sprite file." );
		float scaleX, scaleY;
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &scaleX), "\tScaleX File format invalid! Expecting a float.");
		ASSERT2(1 == fscanf(filePtr, "\t\t%f\n", &scaleY), "\tScaleY File format invalid! Expecting a float.");
		newEntry->second.emplace_back(enemyName, enemyTypeIndex, scaleX, scaleY, spriteFileName);//vê se esse uso consegue instanciar a struct, caso contrário criar construtor
	}
	//agora é ler o waveData
//	fscanf(filePtr, "--WAVES--\n");
	//ASSERT2(0 == ferror(filePtr), "\tFile format invalid! Expecting \"--WAVES--\".");
	char waveName[WAVE_NAME_MAX_LENGHT+1];
	waveName[WAVE_NAME_MAX_LENGHT]= '\0';
	vector<WaveData> &waveVec= newEntry->first;
	while(1== fscanf(filePtr, " %s\n", waveName) ){
		std::cout <<  WHERE<< "\t\t" << waveName << END_LINE;
		//printf("\nwaveName : %s",waveName);
		//TEMP_REPORT_I_WAS_HERE;
		waveVec.emplace_back();

		//std::cout<< "debug waveVec.Size-1 : ";
		//std::cout << waveVec.size()-1 << "\n";

		waveVec[waveVec.size()-1].waveName = waveName;
		vector<SpawnPointData> &spawnPointsVec = waveVec[waveVec.size()-1].spawnPointsData;
		int spawnPoint;
		ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
		TEMP_REPORT_I_WAS_HERE;
		while(1 == fscanf(filePtr, " SpawnPoint:%d\n", &spawnPoint)){
			std::cout <<  WHERE<< "\t\t" << spawnPoint << END_LINE;
			spawnPointsVec.reserve(spawnPoint+1);

			//vector<EnemySpawnData> &enemySpawnVector;
			//std::cout << "\nalooocando spawnPoint: ";
			//printf("%d\n", spawnPoint);
			//printf("%d\n", spawnPointsVec[spawnPoint].enemySpawnData);
			//std::cout << std::endl;

			vector<EnemySpawnData> &enemySpawnVector = spawnPointsVec[spawnPoint].enemySpawnData;
			int enemyIndex;
			while(1 == fscanf(filePtr, " %d\n", &enemyIndex) ){
				std::cout <<  WHERE<< "\t\t" << enemyIndex << END_LINE;

				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				int numberOfEnemies;
				ASSERT2(1 == fscanf(filePtr, "\t\t%d\n", &numberOfEnemies), "\tFile format invaled! Expecting a integer.");
				int enemyHP;
				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				ASSERT2(1 == fscanf(filePtr, "\t\t%d\n", &enemyHP), "\tFile format invaled! Expecting a integer.");
				uint endPoint;
				ASSERT2(0 == ferror(filePtr), "\tFile format invalid!.");
				ASSERT2(1 == fscanf(filePtr, "\t\t%u\n", &endPoint), "\tFile format invaled! Expecting a integer.");
				REPORT_DEBUG2(1, "\t enemyIndex= " << enemyIndex);
				REPORT_DEBUG2(1, "\t numberOfEnemies= " << numberOfEnemies);
				REPORT_DEBUG2(1, "\t enemyHP= " << enemyHP);
				REPORT_DEBUG2(1, "\t endPoint= " << endPoint);
				if(ferror(filePtr)){
					break;
				}
				TEMP_REPORT_I_WAS_HERE;
				enemySpawnVector.emplace_back(enemyIndex, numberOfEnemies, enemyHP, endPoint);
				TEMP_REPORT_I_WAS_HERE;
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
//void GameResources::SaveWeightData(std::array<std::map<int, int> *data)

//void GameResources::SaveWaveData(voidstd::pair<std::vector<WaveData>, std::vector<EnemyData> > *data);

