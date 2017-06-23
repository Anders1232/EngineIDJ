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
<<<<<<< HEAD
		/**
			\brief Obtém string a partir de EnemyType

		*/
		static std::string GetStringFromEnemyType(EnemyType type);
=======
		static void Clear(void);
>>>>>>> a3fd237d23ea080d695000cc63486c2d1c2fdfed
//		static void SaveWeightData(std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE > &data);
//		static void SaveWaveData(std::pair<std::vector<WaveData>, std::vector<EnemyData> > &data);
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
<<<<<<< HEAD
		static std::unordered_map<std::string, std::shared_ptr<std::array<std::map<int, double>, EnemyType::ENEMY_TYPE_SIZE> > > weightDataMap;/**<Mapa de WeightData indexada pelo nome do arquivo.*/
		static std::unordered_map<std::string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > waveDataMap;/**<Mapa de WaveData indexado pelo nome do arquivo.*/
=======
		static std::unordered_map<string, std::shared_ptr<std::array<std::map<int, int>, EnemyType::ENEMY_TYPE_SIZE > > > weightDataMap;/**<Mapa de WeightData indexada pelo nome do arquivo.*/
		static std::unordered_map<string, std::shared_ptr<std::pair<std::vector<WaveData>, std::vector<EnemyData> > > > waveDataMap;/**<Mapa de WaveData indexado pelo nome do arquivo.*/

>>>>>>> a3fd237d23ea080d695000cc63486c2d1c2fdfed
};

#endif // GAMERESOURCES_H
