#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "AStarHeuristic.h"

class ManhattanDistance : public AStarHeuristic
{
	public:
		ManhattanDistance();
		int operator()(Vec2 origiTile, Vec2 destTile);
};

#endif // MANHATTANDISTANCE_H
