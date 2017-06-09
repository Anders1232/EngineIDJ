#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <string>
#include <WaveData.h>

class GameResources
{
	public:
		GameResources();
		
		std::shared_ptr<std::array<std::map<int, int>, EnemyType::SIZE> > GetWeightData(std::string file);
		std::pair<std::shared_ptr<std::vector<WaveData>>, std::shared_ptr<std::vector<EnemyData>> >  GetWaveData(std::string file);
};

#endif // GAMERESOURCES_H
