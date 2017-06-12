#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <map>
#include "WaveData.h"
#include "Enemy.h"

class GameResources{
	public:
		GameResources();
		static std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > GetWeightData(std::string file);//para o pathfiding
		static std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > GetWaveData(std::string file);
	private:
		static EnemyType GetEnemyTypeFromString(std::string);
		static void ReadWaveData(std::string file);
		static void ReadWeightData(std::string file);
		static void SaveWeightData(std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE > &data);
		static void SaveWaveData(std::pair<std::vector<WaveData>, std::vector<EnemyData> > &data);
		static std::unordered_map<std::string, std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE> > > weightDataMap;
		static std::unordered_map<std::string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > waveDataMap;
};

#endif // GAMERESOURCES_H
