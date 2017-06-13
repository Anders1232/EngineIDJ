#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"

#ifndef TOWER_H
#define TOWER_H

#define TOWER_BASE_HP (500)
#define TOTAL_TOWER_TYPES 5


class Tower : public GameObject{
	public:
		/**
			\brief Tipos de Torres

			Enumeração com os tipos de torres possíveis.
		*/
		typedef enum TowerType : int{
			MEDICINE=0,
			SOCIOLOGY,
			ENGINEERING,
			ARTS,
			COMPUTATION
		} TowerType;
		
		Tower(TowerType, float x, float y, Vec2 tileSize, TileMap *tileMap);
		void Damage(int damage);
	
		void Update(float dt );
		void Render(void);
		bool IsDead(void);
		void RequestDelete(void);
		
		void NotifyCollision(GameObject &other);
		Rect GetWorldRenderedRect(void) const;
		bool Is(string type);
		~Tower();
	private:
		Sprite sp;
		int hitpoints;
		bool isDraging;
};

#endif // TOWER_H
