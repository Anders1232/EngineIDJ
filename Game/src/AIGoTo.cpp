#include "AIGoTo.h"

AIGoTo::AIGoTo(float speed,int dest,TileMap& tilemap,GameObject &associated):speed(speed),destTile(dest),tileMap(tilemap),associated(associated){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	path = tileMap.AStar(tileMap.GetTileMousePos(Vec2(associated.box.x,associated.box.y), false, 0),destTile,heuristic,tileWeightMap);
	vecSpeed = Vec2(0.0,0.0);

}

void AIGoTo::Update(float dt){


	if(!path.empty()){

		tempDestination = Vec2(tileMap.GetTileSize().x * (path.front() % tileMap.GetWidth()),tileMap.GetTileSize().y*(path.front() / tileMap.GetWidth()));
		float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
			
		if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){

			associated.box.x = (tempDestination.x - (associated.box.w/2));
			associated.box.y = (tempDestination.y - (associated.box.h/2));
			path.pop_front();

			if(!path.empty()){

				tempDestination = Vec2(tileMap.GetTileSize().x * (path.front() % tileMap.GetWidth()),tileMap.GetTileSize().y*(path.front() / tileMap.GetWidth()));
				float weight = tileWeightMap.at(tileMap.AtLayer(path.front(),WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
			}
		}
		else if(vecSpeed.Magnitude() == 0.0){

			float weight = tileWeightMap.at(tileMap.AtLayer(path.front(),WALKABLE_LAYER));
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