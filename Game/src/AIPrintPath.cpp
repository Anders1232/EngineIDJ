#include "AIPrintPath.h"

AIPrintPath::AIPrintPath(TileMap* tilemap,GameObject &associated):tilemap(tilemap),associated(associated){

	heuristic = new ManhattanDistance();

}

void AIPrintPath::Update(float dt){

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){

		Vec2 mousePos = Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos());
		dest = tilemap->GetCoordTilePos(mousePos, false, 0);
		if(associated.Is("Enemy")){

			Vec2 pos = Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y);
			int position = tilemap->GetCoordTilePos(pos, false, 0);
			std::map<int, double> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
			/*std::cout << position << " " << dest << std::endl;
			std::cout << weightMap.empty() << std::endl;*/
			/*for (auto elem1 : (*GameResources::GetWeightData("map/WeightData.txt"))) {
				for(auto elem2 : elem1){
					std::cout << elem2.first << ":" << elem2.second << std::endl;
				}
				std::cout << std::endl;

			}*/
			std::list<int> path = tilemap->AStar(position,dest,heuristic,weightMap);
			tilemap->ShowPath(path);

		}


	}

}

bool AIPrintPath::Is(ComponentType type) const{
	return (type == ComponentType::AI_PRINT_PATH);
}