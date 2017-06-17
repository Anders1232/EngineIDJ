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
	\brief Classe que gerenci´a as waves do jogo. Responsavel por iniciar, encerrar e contar as waves.
	Mantem a contagem de vidas restantes e inimigos restantes que sao usadas para condiçao de fim de jogo.

	A waveManager e´ um componente. Ela gerencia as waves usando como base os inimigos restantes e vidas restantes.  
*/
class WaveManager : public Component {
	public:
		/**
			\brief Construtor
			\param tileMap Usada para inicializar spawnGroup, um vetor de grupos, e cada grupo, um vetor de spawn points. um vetor de vetor!
			\param waveFile Nome do arquivo aonde sera´ feita a leitura dos dados contendo todas as informaçoes de wave e inimigos do jogo.
		*/

		WaveManager(TileMap& tileMap, string waveFile);
		~WaveManager();
		/**
			\brief Atualiza estado.
			Atualiza o estado da wave atual.
			\param associated. So recebe este argumento por ser um componente. Mas como wave nao faz parte de um GameObject, ele recebe o parametro EmptyGameObject em que nao e´ usada.
			\param dt tempo dt, e´ usado para fazer o spawn de tempos em tempos dos inimigos.
		*/		
		void Update(GameObject &associated, float dt);
		/** 
			\brief Tipo
			Retorna o tipo da componente se e´ igual a WAVE_MANAGER. true ou false.
			\param type Tipo da Compomente a ser comparada com WAVE_MANAGER.
		*/
		bool Is(ComponentType type) const;
		/** 
			\brief Inicializa um nova wave
			reinicia os atributos da classe (	enemyIndex, endWave e waveCount) para executar uma nova wave e conta o novo numero de inimigos restantes.
		*/
		void StartWave();
		/** 
			\brief Verifica Fim de wave
			Verifica se a flag de fim de wave foi acionada. Retorna endWave.
		*/		
		bool EndWave();
		/** 
			\brief Inimigo Chegou ao Destino
			Recebe uma notificaçao da componente HitPoints, se o inimigo foi destruido por chegar ao destino e decrementa o contador de vidas.
		*/				
		void NotifyEnemyGotToHisDestiny();
		/** 
			\brief Inimigo Destruido
			Recebe uma notificaçao se o inimigo foi destruido e decrementa o contador de inimigos restantes.
		*/						
		void NotifyEnemyGotKilled();
		/** 
			\brief Pegar vidas Restantes
			\return playerLifes: vidas restantes
			Retorna as vidas restantes da wave atual
		*/						
		int GetLifesLeft();
		/** 
			\brief Pegar inimigos Restantes
			\return enemiesLeft: inimigos restantes
			Retorna os inimigos restantes da wave atual
		*/		
		int GetEnemiesLeft();
	private:
		void SpawnEnemy(int tileMapPosition, int enemyId,uint baseHP, uint endPoint);
		vector<vector<int>> *spawnGroups;/**<Armazena o vetor de SpawnGroup, cada spawnGroup armazena um vetor de spawnPoint.*/
		static int waveCount; /**<Contador de waves restantes. Tbm usado para nivelar as waves.*/
		Timer spawnTimer; /**<**/
		
		int enemiesLeft;/**<Contador de inimigos restantes da wave atual.*/
		int playerLifes;/**<Contador de inimigos restantes da wave atual.*/

		TileMap &tileMap;/**<Endereço de TileMap. Usado para conseguir spwanGroups */
		bool endWave; /**<Flag de fim da wave atual. true se a level acabou.*/
		std::shared_ptr< std::pair< std::vector<WaveData>, std::vector<EnemyData> > > wavesAndEnemysData; /**<Shared Pointer QUe vai armazenar a leitura do arquivo com as informaçoes de Wave e Inimigo.*/
		int waveIndex, enemyIndex, totalWaves;/**<Identificador da wave atual, identificador do inimigo atual e o contador de waves. Vitoria se da quando contador for igual ao numero total.*/



};

#endif