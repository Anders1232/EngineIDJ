#include "GameObjectTileMap.h"
#include "InputManager.h"
#include "Error.h"

GameObjectTileMap::GameObjectTileMap(std::sting tileMapFile, std::string collisionTileMapFile, Vec2 tileSize)
	: TileMap(tileMapFile.c_str(), nullptr), gameObjectMatrix(GetWidth()*GetHeight()*GetDepth(), nullptr), draggingGO(nullptr){
}

void GameObjectTileMap::DragAndAddGameObject(GameObject *obj){
	if(nullptr == draggingGO){
		draggingGO= obj;
	}
	else{
		std::cout << WHERE << "[WARNING] tentou-se arrastar mais de um gameObject" << END_LINE;
	}
}


void GameObjectTileMap::Update(void){
	if(nullptr != draggingGO){
		InputManager &inputManager= InputManager::GetInstance();
		if(inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)){
			TEMP_REPORT_I_WAS_HERE;
			draggingGO->box= inputManager.GetMousePos()-(Vec2(draggingGO->box.w, draggingGO->box.h)*0.5f);
		}
		else{
			TEMP_REPORT_I_WAS_HERE;
			InsertGO(draggingGO);
			draggingGO= nullptr;
		}
	}
}


void GameObjectTileMap::InsertGO(GameObject* obj){
	Vec2 mousePos= InputManager::GetInstance().GetMousePos();
	int position= GetTileMousePos(mousePos, true, 0);
	if(0 == tileMatrix.at(position)){
		gameObjectMatrix[position]= obj;
	}
	else if (0 > tileMatrix[position]){
		std::cout << WHERE << "tentado inserir objeto em posição inválida" << END_LINE;
	}
	else{
		std::cout << WHERE << "tentado inserir objeto em posição já ocupada!" << END_LINE;
	}
}

void GameObjectTileMap::Render(int cameraX, int cameraY) const{
//	TileMap::Render(cameraX, cameraY);
	for(unsigned int count =0 ; count < gameObjectMatrix.size(); count++){
		GameObject *go= gameObjectMatrix[count];
		if(nullptr != go){
			go->Render();
		}
	}
	if(nullptr != draggingGO){
//		TEMP_REPORT_I_WAS_HERE;
		draggingGO->Render();
	}
}

