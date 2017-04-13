#ifndef ANIMATION_H
#define ANIMATION_H

#include "Gameobject.h"
#include "Timer.h"
#include "Sprite.h"

class Animation: public GameObject
{
	public:
		Animation
		(
			float x,
			float y,
			float rotation,
			string sprite,
			int frameCount,
			float frameTime,
			bool ends
		);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(string type);
	private:
		Timer endTimer;
		float timeLimit;
		bool onetimeOnly;
		Sprite sp;
};

#endif // ANIMATION_H
