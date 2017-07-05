#ifndef GAMEOBJECTFINDER_H
#define GAMEOBJECTFINDER_H

#include "Vec2.h"
#include "GameObject.h"

class NearestGOFinder{
	public:
		virtual GameObject* FindNearestGO(Vec2 origin, std::string type) = 0;
		virtual ~NearestGOFinder(){};
};

#endif // GAMEOBJECTFINDER_H
