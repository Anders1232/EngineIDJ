#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"
#include "Timer.h"
#include "TileMap.h"
#include "Component.h"
#include "WaveData.h"
#include "Error.h"
#include <memory>
using std::vector;

/**
	\brief Classe que gerencia as waves do jogo. Responsavel por iniciar, encerrar e contar as waves. Também gerencia o spawn dos inimigos na wave atual.
	Mantem a contagem de vidas restantes e inimigos restantes que sao usadas para condição de fim de jogo.

	A waveManager é um componente. Ela gerencia as waves usando como base os inimigos restantes e vidas restantes.
*/
class WaveManager : public Component {
	public:
		/**
			\brief Construtor.
			\param tileMap Usada para inicializar spawnGroup, um vetor de grupos, e cada grupo, um vetor de spawn points. Um vetor de vetor!
			\param waveFile Nome do arquivo aonde será feita a leitura dos dados contendo todas as informações de wave e inimigos do jogo.
		*/
		WaveManager(TileMap& tileMap, string waveFile);
		/**
			\brief Destrutor.
			Destrói o ponteiro de spawnGroups.
		*/
		~WaveManager();
		/**
			\brief Atualiza estado.
			Atualiza o estado da wave atual.
			\param associated. So recebe este argumento por ser um componente. Mas como wave nao faz parte de um GameObject, ele recebe o parametro EmptyGameObject em que nao é usada.
			\param dt tempo dt, é usado para fazer o spawn de tempos em tempos dos inimigos.
		*/
		void Update(GameObject &associated, float dt);
		/** 
			\brief Tipo
			Retorna o tipo da componente se é igual a WAVE_MANAGER. true ou false.
			\param type Tipo da Compomente a ser comparada com WAVE_MANAGER.
		*/
		bool Is(ComponentType type) const;
		/** 
			\brief Inicializa um nova wave.
			reinicia os atributos da classe (enemyIndex, endWave e waveCount) para executar uma nova wave e conta o novo número de inimigos restantes.
		*/
		void StartWave();
		/** 
			\brief Verifica Fim de wave.
			Verifica se a flag de fim de wave foi acionada. Retorna endWave.
		*/
		bool EndWave();
		/** 
			\brief Inimigo Chegou ao Destino.
			Recebe uma notificação da componente HitPoints, se o inimigo foi destruido por chegar ao destino e decrementa o contador de vidas.
		*/
		void NotifyEnemyGotToHisDestiny();
		/**
			\brief Inimigo Destruido.
			Recebe uma notificação se o inimigo foi destruido e decrementa o contador de inimigos restantes.
		*/
		void NotifyEnemyGotKilled();
		/** 
			\brief Pegar vidas Restantes.
			\return playerLifes: vidas restantes.
			Retorna as vidas restantes da wave atual.
		*/
		int GetLifesLeft();
		/** 
			\brief Pegar inimigos Restantes.
			\return enemiesLeft: Inimigos restantes.
			Retorna os inimigos restantes da wave atual.
		*/
		int GetEnemiesLeft();
		/** 
			\brief Condiçao de Vitoria.
			\return victory: verdadeiro se as waves acabaram.
			Retorna true se a condiçao de vitoria foi satisfeita.
		*/
		bool Victory();
	private:
		/**
			\brief Criar um novo inimigo no mapa.
			\param tileMapPosition: Posição do tileMap. Usado para calcular a posição exata de spawn do inimigo.
			\param enemyId: identificador de inimigo no waveData.
			\param baseHP: HP base do inimigo para a wave atual.
			\param endPoint: posição de destino para aonde o inimigo vai. Lido de WaveData.
			
		*/
		void SpawnEnemy(int tileMapPosition, int enemyId,uint baseHP, uint endPoint, uint indexOfTheEnemyToSpawn);
		vector<vector<int>> *spawnGroups;/**<Armazena o vetor de SpawnGroup, cada spawnGroup armazena um vetor de spawnPoint.*/
		vector<vector<int>> *endGroups;/**<Armazena o vetor de SpawnGroup, cada spawnGroup armazena um vetor de spawnPoint.*/
		static int waveCount; /**<Contador de waves restantes. Também usado para nivelar as waves.*/
		Timer spawnTimer; /**<Contador para o cooldown de respawn. **/
		
		int enemiesLeft;/**<Contador de inimigos restantes da wave atual.*/
		int playerLifes;/**<Contador de inimigos restantes da wave atual.*/

		TileMap &tileMap;/**<Endereço de TileMap. Usado para conseguir spwanGroups */
		bool endWave; /**<Flag de fim da wave atual. true se a level acabou.*/
		std::shared_ptr< std::pair< std::vector<WaveData>, std::vector<EnemyData> > > wavesAndEnemysData; /**<Shared Pointer, vai armazenar a leitura do arquivo com as informaçoes de Wave e Inimigo.*/
		int waveIndex, enemyIndex, totalWaves;/**<Identificador da wave atual, identificador do inimigo atual e o contador de waves. Vitória se da quando contador for igual ao número total.*/
		int waveTotalEnemies; /**<Indica o número total de inimigos da wave atual.*/

		int maxNumberOfEnemiesInSpawnPoint; /**<Numero maximo de um tipo de inimigo dentro de uma SpawnGroup. */
		bool victory;/**< Verdadeiro se o jogador passou por todas as waves com vidas restantes. */

};

#endif
