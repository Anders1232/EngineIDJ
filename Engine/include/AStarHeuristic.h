#include "TileMap.h"
class AStarHeuristic{

	AStarHeuristic();

	int operator()(int originTile,int destTile ,TileMap tilemap);


};