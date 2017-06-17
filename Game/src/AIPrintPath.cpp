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
			std::map<int, double> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
			std::cout << position <<"-" <<dest << std::endl;
			std::cout << weightMap.empty() << std::endl;
			for(auto elem : weightMap){
				
				std::cout << elem.first <<"-" <<elem.second << std::endl;

			}
			std::list<int> path = tilemap->AStar(position,dest,heuristic,weightMap);
			/*for(std::list<int>::iterator it = path.begin(); it != path.end(); ++ it){

			std::cout << *it <<" " << std::endl;

			}
			
			tilemap->ShowPath(path);*/

		}


	}

}

bool AIPrintPath::Is(ComponentType type) const{
	return (type == ComponentType::AI_PRINT_PATH);
}