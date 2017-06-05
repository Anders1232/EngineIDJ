#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "AStarHeuristic.h"

class ManhattanDistance : public AStarHeuristic
{
	public:
		ManhattanDistance();
		int operator()(int originTile,int destTile ,TileMap &tilemap);
};

#endif // MANHATTANDISTANCE_H
