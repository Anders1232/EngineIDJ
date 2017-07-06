#ifndef AURA_H
#define AURA_H

#include "Enemy.h"
#include "Component.h"
#include "Timer.h"
#include "NearestGOFinder.h"

class Aura: public Component
{
	public:
		Aura(GameObject& associated, Enemy::Event auraType, float auraRange, float timeBetweetNotifications, NearestGOFinder &finder);
		~Aura(void);
		void Update(float dt);
		void Render(void);
		bool Is(ComponentType type);
	private:
		GameObject &associated;
		Enemy::Event auraType;
		float auraRange;
		Sprite sp;
		Sprite sp2;
		float timeBetweetNotifications;
		Timer notificationTimer;
		NearestGOFinder &finder;
};

#endif // AURA_H
