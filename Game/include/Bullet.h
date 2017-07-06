#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Sprite.h"
#include "Game.h"
#include "Animation.h"
#include "Vec2.h"
#include <string>

#define BULLET_VEL 210
#define BULLET_REACH 1000

class Bullet: public GameObject
{
	public:
		Bullet(float x,float y,float angle,float speed,float maxDistance,std::string sprite,std::string targetType,float frameTime = 1,int frameCount = 1);
		~Bullet(void);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(string type);
		std::string getTargetType();
	private:
		Sprite sp;
		Vec2 speed;
		float distanceLeft;
		std::string targetType;
};

#endif