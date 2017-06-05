#include "TileMap.h"

class AStarHeuristic{
	virtual AStarHeuristic(){};
	virtual int operator()(int originTile,int destTile ,TileMap &tilemap)=0;
};
