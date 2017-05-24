#ifndef PENGUINS_H
#define PENGUINS_H

#include "Gameobject.h"
#include "Sprite.h"
#include "Timer.h"

#define PENGUIM_MIN_BOX_X (0)
#define PENGUIM_MIN_BOX_Y (0)
#define PENGUIM_MAX_BOX_X (3408)
#define PENGUIM_MAX_BOX_Y (2480)

class Penguins: public GameObject {
	public:
		Penguins(float x, float y);
		~Penguins();
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void RequestDelete(void);
		void Shoot(void);
		void NotifyCollision(GameObject &other);
		bool Is(string type);
		static Penguins *player;
		Rect GetWorldRenderedRect(void) const;
	private:
		Sprite bodySP;
		Sprite cannonSp;
		Vec2 speed;
		float linearSpeed;
		float cannonAngle;
		int hp;
		void CheckMapLimits(void);
};

#endif // PENGUINS_H
