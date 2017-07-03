#include "AIGoDown.h"
AIGoDown::AIGoDown(float speed, int dest, TileMap &tileMap, GameObject &associated, WaveManager &wManager):speed(speed),destTile(dest),tileMap(tileMap), waveManager(wManager){

}
//AIGoDown::AIGoDown(float speed):speed(speed){
//}

void AIGoDown::Update(GameObject &associated, float dt){

	associated.box.y+= speed*dt;
	if(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0) != destTile){
		printf("chegou!\n");
	}

}

bool AIGoDown::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_DOWN);
}
