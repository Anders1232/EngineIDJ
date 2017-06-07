#include "TileMap.h"

class AStarHeuristic{
//	virtual AStarHeuristic(){};
	public:
		virtual int operator()(int originTile,int destTile ,TileMap &tilemap)=0;
};
