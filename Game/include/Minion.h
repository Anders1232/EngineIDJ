#ifndef MINION_H
#define MINION_H

#include "Gameobject.h"
#include "Vec2.h"
#include "Sprite.h"

#define VELOCIDADE_ANGULAR_MINION (2)
#define MINION_DISTANCE_TO_CENTER (150)
#define MINION_BULLET_SPEED (800)
#define MINION_BULLET_MAX_DISTANCE (500)

class Minion: public GameObject
{
	public:
		Minion(GameObject *minionCenter, float arcOffset =0);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void Shoot(Vec2 pos);
		void NotifyCollision(GameObject &other);
		bool Is(string type);
		Rect GetWorldRenderedRect(void) const;
	private:
		GameObject *center;
		Sprite sp;
		float arc;
};

#endif // MINION_H
