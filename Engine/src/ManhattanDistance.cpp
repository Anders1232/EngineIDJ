#include "ManhattanDistance.h"

ManhattanDistance::ManhattanDistance(){
}

int ManhattanDistance::operator()(int originTile,int destTile ,TileMap &tilemap){
	int mapWidth= tilemap.GetWidth();
	int distanceX= (destTile % mapWidth) - (originTile % mapWidth);
	int distanceY= (originTile / mapWidth) - (originTile / mapWidth);
	if(0 > distanceX){
		distanceX= -distanceX;
	}
	if(0 > distanceY){
		distanceY= -distanceY;
	}
	return distanceX+distanceY;
}

