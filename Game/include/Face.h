#include "Gameobject.h"
#include "Sprite.h"
#include "Rect.h"

#ifndef FACE_H
#define FACE_H

class Face : public GameObject
{
	public:
		Face(float x, float y);
		void Damage(int damage);
	
		void Update(float dt );
		void Render();
		bool isDead();
	
		~Face();
	private:
		int hitpoints;
		bool isDraging;
		Sprite sp;
};

#endif