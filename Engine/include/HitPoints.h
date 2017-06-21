#ifndef HITPOINTS_H
#define HITPOINTS_H

#include "Component.h"
#include "Sprite.h"

typedef unsigned int uint;
class HitPoints : public Component {
	public:
		HitPoints(uint baseHp);
		~HitPoints();
		
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType) const;

	private:
		int hp;
		Sprite healthBar;
		Sprite healthColor;
};

#endif