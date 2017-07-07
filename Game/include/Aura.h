#ifndef AURA_H
#define AURA_H

#include "Enemy.h"
#include "Component.h"
#include "Timer.h"
#include "NearestGOFinder.h"

class Aura: public Component
{
	public:
		Aura(GameObject& associated, Enemy::Event auraType, float auraRange, float timeBetweetNotifications, NearestGOFinder &finder, std::string targetType);
		~Aura(void){};
		void Update(float dt);
		void Render(void);
		bool Is(ComponentType type) const;
	private:
		GameObject &associated;
		Enemy::Event auraType;
		float auraRange;
		Sprite sp;
		Sprite sp2;
		float timeBetweetNotifications;
		Timer notificationTimer;
		NearestGOFinder &finder;
		std::string targetType;
};

#endif // AURA_H
