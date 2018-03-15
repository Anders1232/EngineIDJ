#include "AIGoTo.h"

AIGoTo::AIGoTo(float speed,int dest,TileMap& tilemap,GameObject &associated):speed(speed),destTile(dest), pathIndex(0),associated(associated),tileMap(tilemap){
	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("./assets/map/WeightData.txt"))[((Enemy&)associated).GetType()];
	Vec2 originCoord= associated.box.Center();
	path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "./assets/map/WeightData.txt");
	vecSpeed = Vec2(0.0,0.0);
}

AIGoTo::~AIGoTo(void){
	delete heuristic;
}

void AIGoTo::Update(float dt){
	if(pathIndex != path->size()){
		tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
		float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
		if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){
			associated.box.x = (tempDestination.x - (associated.box.w/2));
			associated.box.y = (tempDestination.y - (associated.box.h/2));
			pathIndex++;
			if(pathIndex != path->size()){
				tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
				float weight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
			}
		}
		else if(vecSpeed.Magnitude() == 0.0){
			float weight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
			vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
		}
		else{
			associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
			associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);
		}
	}
}

bool AIGoTo::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_TO);
}
