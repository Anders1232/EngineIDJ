#include "Gameobject.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"

#ifndef FACE_H
#define FACE_H

class Face : public GameObject
{
	public:
		Face(float x, float y, Vec2 tileSize, TileMap *tileMap);
		void Damage(int damage);
	
		void Update(float dt );
		void Render();
		bool IsDead(void);
		
		void NotifyCollision(GameObject &other);
		Rect GetWorldRenderedRect(void) const;
		bool Is(string type);
		~Face();
	private:
		int hitpoints;
		bool isDraging;
		Sprite sp;
};

#endif
