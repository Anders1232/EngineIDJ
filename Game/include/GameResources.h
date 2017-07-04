#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <memory>
#include <array>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <map>
#include <cstdint>
#include "WaveData.h"
#include "Enemy.h"

/**
	\brief Classe estática que gerencia recursos específicos do jogo
	
	Turbinando ela para instanciar diferentes tipos de componentes/sprites essa classe provavelmente se manterá no projeto até o final.
*/
class GameResources{
	public:
		/**
			\brief Obtém WeightData a partir de arquivo.

			Obtém referência para informações do WeightData do nome do arquivo informado, se as informações do arquivo informado não tiverem sido carregadas elas o serão.
			Arquivo não existente ou em formato inválido faz com que Error() seja chamada, gerando uma interrupção do programa.
		*/
		static std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > GetWeightData(std::string file);//para o pathfiding
		/**
			\brief Obtém WaveData a partir de arquivo.

			Obtém referência para informações do WaveData do nome do arquivo informado, se as informações do arquivo informado não tiverem sido carregadas elas o serão.
			Arquivo não existente ou em formato inválido faz com que Error() seja chamada, gerando uma interrupção do programa.
		*/
		static std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > GetWaveData(std::string file);
		static void Clear(void);
//		static void SaveWeightData(std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE > &data);
//		static void SaveWaveData(std::pair<std::vector<WaveData>, std::vector<EnemyData> > &data);
		static void SetTileMap(TileMap*);
		static void NotifyTileMapChanged(void);
		static std::shared_ptr<std::vector<int> > GetPath(EnemyType type, AStarHeuristic *heuristic, int origin, int dest, std::string weightDataFile);
	private:
		/**
			\brief Construtor que não deve ser implementado

			Essa classe é para ser puramente estática. Essa classe não deve ser instanciada,por isso temos um contrutor declarado mas não implementado.
		*/
		GameResources();
		/**
			\brief Obtém EnemyType a partir de screen

			Método utilizado internamente para se obter o EnemyType a partir da string(geralmente lida a partir de arquivo).
		*/
		static EnemyType GetEnemyTypeFromString(std::string);
		static std::string GetEnemyTypeStringFromType(EnemyType);
		/**
			\brief Lê WaveData.

			Lê o WaveData a partir do arquivo informado.
			Arquivo não existente ou em formato inválido faz com que Error() seja chamada, gerando uma interrupção do programa.
		*/
		static void ReadWaveData(std::string file);
		/**
			\brief Lê WeightData.

			Lê o WeightData a partir do arquivo informado.
			Arquivo não existente ou em formato inválido faz com que Error() seja chamada, gerando uma interrupção do programa.
		*/
		static void ReadWeightData(std::string file);
		static std::unordered_map<std::string, std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > > weightDataMap;/**<Mapa de WeightData indexada pelo nome do arquivo.*/
		static std::unordered_map<std::string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > waveDataMap;/**<Mapa de WaveData indexado pelo nome do arquivo.*/
		static std::unordered_map<std::string, std::pair<uint, std::shared_ptr<std::vector<int> > > >pathMap;
		static TileMap *tileMap;
		static uint lastMapUpdate;
};

#endif // GAMERESOURCES_H
