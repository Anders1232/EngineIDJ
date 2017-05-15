#include "GameObjectTileMap.h"
#include "InputManager.h"
#include "Error.h"

GameObjectTileMap::GameObjectTileMap(std::string collisionTileMapFile)
	: TileMap(collisionTileMapFile.c_str(), nullptr){
	
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
