#include "ManhattanDistance.h"

ManhattanDistance::ManhattanDistance(){
}

<<<<<<< HEAD
int ManhattanDistance::operator()(Vec2 originTile, Vec2 destTile){
	/*int mapWidth= tilemap.GetWidth();
	int distanceX= (limitPoints.y % mapWidth) - (limitPoints.x % mapWidth);
	int distanceY= (limitPoints.x / mapWidth) - (limitPoints.x / mapWidth);
=======
int ManhattanDistance::operator()(Vec2 origin, Vec2 destiny){
	int distanceX= origin.x - destiny.x;
	int distanceY= origin.y-destiny.y;
>>>>>>> 1d905df0f77373565eab9437c6f4abed513fd5fc
	if(0 > distanceX){
		distanceX= -distanceX;
	}
	if(0 > distanceY){
		distanceY= -distanceY;
	}
	return distanceX+distanceY;
}

