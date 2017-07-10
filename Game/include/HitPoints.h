#ifndef HITPOINTS_H
#define HITPOINTS_H

#include "Component.h"
#include "Sprite.h"
#include "Error.h"

class HitPoints : public Component{
	public:
		HitPoints(uint baseHp,GameObject &associated, float scaleX = 0);
		~HitPoints();
		void Update(float dt);
		void RequestDelete(void);
		void Damage(int damage);
		bool Is(ComponentType) const;
		int GetHp();
		void Render();
	private:
		int hp;
		int maxHp;
		Sprite healthBar;
		Sprite healthColor;
		GameObject &associated;
};

#endif // HITPOINTS_H
