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

#define BASE_HIT_POINTS 100
#define DIFICULTY_CONSTANT 12
#define ENEMY_MOVE_SPEED (120.)

enum EnemyType{
	HOSTILE=0,
	NEUTRAL=1,
	ENGINEER=2,
	ARQUITET=3,
	ART=4,
	QUIMIC=5,
	ENEMY_TYPE_SIZE=6
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
		Enemy(Vec2 position, int life); // calcula vida e velocidade 
		Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint);
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
	
	private:
		EnemyType type;/**< Tipos de inimigos, no momento não está sendo utilizado.*/
		Sprite sp;/**< Sprite do inimigo.*/
		Sprite bodySpName;
		Sprite headSpName;
		Sprite pantsSpName;
		Sprite spName;

		bool dead;/**< Armazena se a instância atual deve ser destruída.*/
		
		int enemyIndex; 
		uint quant, baseHP, endPoint;
};

#endif // ENEMY_H
