#ifndef HITPOINTS_H
#define HITPOINTS_H

#include "Component.h"
#include "Sprite.h"

class HitPoints : public Component {
	public:
		HitPoints(uint baseHp);
		~HitPoints();
		
		void Update(GameObject &associated, float dt);
		void Damage(int damage);
		bool Is(ComponentType) const;
		int GetHp();
	private:
		int hp;
		Sprite healthBar;
		Sprite healthColor;
};

#endif