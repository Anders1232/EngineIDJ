#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"

#ifndef FACE_H
#define FACE_H

#define FACE_HP (500)


class Face : public GameObject{
	public:
		Face(float x, float y, Vec2 tileSize, TileMap *tileMap);
		void Damage(int damage);
	
		void Update(float dt );
		void Render(void);
		bool IsDead(void);
		void RequestDelete(void);
		
		void NotifyCollision(GameObject &other);
		Rect GetWorldRenderedRect(void) const;
		bool Is(string type);
		~Face();
	private:
		Sprite sp;
		int hitpoints;
		bool isDraging;
};

#endif
