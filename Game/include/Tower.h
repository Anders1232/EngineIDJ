#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"
#include "Vec2.h"
#include "HitPoints.h"
#include "Bullet.h"

#ifndef TOWER_H
#define TOWER_H

#define TOWER_BASE_HP (100)
#define TOTAL_TOWER_TYPES 5
#define TOWER_BULLET_DAMAGE 10


class Tower : public GameObject{
	public:
		/**
			\brief Tipos de Torres

			Enumeração com os tipos de torres possíveis.
		*/
		typedef enum TowerType : int{
			SMOKE=0,
			ANTIBOMB,
			STUN,
			SHOCK
		} TowerType;
		
		Tower(TowerType type, Vec2 pos, Vec2 tileSize,int hp);
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
		HitPoints *hitpoints;
		bool isDraging;
};

#endif // TOWER_H
