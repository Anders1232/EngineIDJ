#ifndef AIGODOWN_H
#define AIGODOWN_H

#include "Component.h"

class AIGoDown
{
	public:
		AIGoDown(float speed);
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const;
	private:
		float speed;
};

#endif // AIGODOWN_H
