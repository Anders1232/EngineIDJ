#include "AStarHeuristic.h"
#include "TileMap.h"
#include <list>

class AStarOnTilemap{


	AStarOnTilemap();

	std::list<int> operator()(int originTile,int destTile ,TileMap tilemap,Heuristic heuristic);


};