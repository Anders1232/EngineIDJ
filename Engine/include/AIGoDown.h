#ifndef AIGODOWN_H
#define AIGODOWN_H

#include "Component.h"

class AIGoDown
{
	public:
		AIGoDown();
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType type) const
};

#endif // AIGODOWN_H
