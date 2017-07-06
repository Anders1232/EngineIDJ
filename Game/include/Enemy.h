#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Timer.h"
#include "Error.h"
#include "WaveData.h"
#include "HitPoints.h"
#include "Sound.h"
#include "WaveManager.h"
//#include "componentType.h"

#define BASE_HIT_POINTS 100
#define DIFICULTY_CONSTANT 12
#define ENEMY_BULLET_DAMAGE 10
#define ENEMY_MOVE_SPEED (10000.)
#define ENEMY_HOSTILE_MOVE_SPEED (16000.)
#define ENEMY_QUIMIC_MOVE_SPEED (11000.)
#define ENEMY_ENGINEER_MOVE_SPEED (11000.)
#define ENEMY_ARQUITET_MOVE_SPEED (15000.)
#define ENEMY_ART_MOVE_SPEED (10000.)

/**
	\brief Enum que informa o tipo do inimigo
	
	Cada inimigo e´ composto por um tipo, e cada tipo tem suas propriedades diferentes.
*/
enum EnemyType{
	HOSTILE=0,
	NEUTRAL,
	ENGINEER,
	ARQUITET,
	MEDIC,
	ART,
	QUIMIC,
	ENEMY_TYPE_SIZE
};

/**
	\brief Enum que diz a orientaçao do inimigo
	
	Refere-se a algum dos 4 lados que o inimigo pode estar de frente.
*/
enum EnemyDirections{
	UP=0,
	RIGHT=1,
	DOWN=2,
	LEFT=3,
	ENEMY_DIRECTIONS_SIZE=4
};


/**
	\brief Classe que modela inimigos
	
	Turbinando ela para instanciar diferentes tipos de componentes/sprites essa classe provavelmente se manterá no projeto até o final.
*/
class Enemy : public GameObject
{
	public:
		/**
			\brief Construtor
			\param position posição onde o inimigo deve ser instancido.
			\param life Quantidade de vida que o inimigo deve ter.
			
			No momento a position informa o extremo superior esquedo a partir do qual o gameObject será instanciado.
		*/
		Enemy(Vec2 position,EnemyType type, int life); // calcula vida e velocidade 
		/**
			\brief Construtor
			\todo Documentar!
			\todo Verificar se está sendo usado.
			\param position posição onde o inimigo deve ser instancido.
			\param life Quantidade de vida que o inimigo deve ter.
			
			No momento a position informa o extremo superior esquedo a partir do qual o gameObject será instanciado.
		*/
		Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint, TileMap &tileMap, WaveManager &wManager);
		/**
			\brief Destrutor
			
			Destrói todas a suas componentes.
		*/
		~Enemy();
		/**
			\brief Atualiza estado
			
			Chama o método Update de todas as suas componentes.
		*/
		void Update(float dt);
		/**
			\brief Atualiza estado
			
			Chama o método Update de todas as suas componentes.
		*/
		void Render(void);
		/**
			\brief Verifica se esse GameObject deve ser destruído.
			
			Se necessário pode consultar suas componentes para tal, mas o ideal que é as componentes informem isso ao GameObject antes, pela chamado do método RequestDelete.
		*/
		bool IsDead(void);
		/**
			\brief Solicita que esse GaeObject seja destruído
			
			Deve fazer o necessário para que futuras chamadas a IsDead retornem verdadeiro.
		*/
		void RequestDelete(void);
		/**
			\brief Notifica evento de colisão.
			\todo Verificar viabilidade de tratar colisão em componentes.
			
			No momento não faz nada.
		*/
		void NotifyCollision(GameObject &object);
		/**
			\brief Identifica tipo de GameObject.
			\todo Verificar viabilidade de usar enum no lugar de string
			
			Retorna verdadeiro se type for "Enemy", falso caso contrário.
		*/
		bool Is(string type);
		/**
			\brief Obtém rect do GameObject renderizado na tela
			
			Utilizado para verificar onde o mouse está.
		*/
		Rect GetWorldRenderedRect(void) const;
		/**
			\brief Obtém o type do objeto inimigo.
			
		*/
		EnemyType GetType(void) const;
	private:
		void UpdateEnemyDirection(Vec2 lastPosition);
		EnemyType type;/**< Tipos de inimigos, no momento não está sendo utilizado.*/
		std::vector<std::vector<Sprite>> sp;/**< Sprite do inimigo.*/
		bool dead;/**< Armazena se a instância atual deve ser destruída.*/
		int enemyIndex;/**<Identificador do inimigo */
		HitPoints *hitpoints;/**< Ponteiro para a componente HitPoints. Usada para chamada com argumentos. */
		uint baseHP, endPoint; /**< Respectivamentes a vida base do inimigo e seu ponto de destino. */
		EnemyDirections direction; /**< Direçao para aonde a sprite do inimigo esta voltada. Norte, Sul, Leste ou Oeste */
		Sound walkingSound;
};

#endif // ENEMY_H
