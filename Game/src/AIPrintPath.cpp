#include "AIPrintPath.h"

AIPrintPath::AIPrintPath(TileMap* tilemap):tilemap(tilemap){

	heuristic = new ManhattanDistance();

}

void AIPrintPath::Update(GameObject& associated,float dt){

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {

		Vec2 mousePos = Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos());
		dest = tilemap->GetTileMousePos(mousePos, false, 0);
		if(associated.Is("Enemy")){

			Vec2 pos = Camera::ScreenToWorld(((Enemy&)associated).box);
			int position = tilemap->GetTileMousePos(pos, false, 0);
			std::map<int, int> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
			std::cout << "chegou aqui" << std::endl;
			tilemap->ShowPath(tilemap->AStar(position,dest,heuristic,weightMap));

		}


	}

}

bool AIPrintPath::Is(ComponentType type) const{
	return (type == ComponentType::AI_PRINT_PATH);
}