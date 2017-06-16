#include "AIPrintPath.h"

AIPrintPath::AIPrintPath(int dest,TileMap* tilemap):dest(dest),tilemap(tilemap){

	heuristic = new ManhattanDistance();
}

void AIPrintPath::Update(GameObject& associated,int newDest){

	if(associated.Is("Enemy")){
		if((newDest != dest && !path.empty()) || path.empty()){

			dest = newDest;
			Vec2 pos = Camera::ScreenToWorld(((Enemy&)associated).box);
			int position = tilemap->GetTileMousePos(pos, false, 0);
			tilemap->ShowPath(tilemap->AStar(position,dest,heuristic,(*GameResources::GetWeightData("WeightData.txt"))[((Enemy&)associated).GetType()]));

		}


	}

}

bool AIPrintPath::Is(ComponentType type) const{
	return (type == ComponentType::AI_PRINT_PATH);
}