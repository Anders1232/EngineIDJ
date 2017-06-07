#ifndef ASTAR_H
#define ASTAR_H

#include "Vec2.h"

class AStarHeuristic{
//	virtual AStarHeuristic(){};
	public:
		virtual int operator()(Vec2 origin, Vec2 destiny) = 0;
};

#endif