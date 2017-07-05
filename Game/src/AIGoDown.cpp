#include "AIGoDown.h"

AIGoDown::AIGoDown(float speed, int dest, TileMap &tileMap, WaveManager &wManager, GameObject &associated):speed(speed),destTile(dest),tileMap(tileMap), waveManager(wManager), associated(associated){
}

//void AIGoDown::Update(GameObject &associated, float dt){

void AIGoDown::Update(float dt){
	associated.box.y+= speed*dt;
	/*
	if(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0) != destTile){
		printf("nao chegou\n");
	}else{
		printf("chegou!\n");
	}
	*/
}

bool AIGoDown::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_DOWN);
}
