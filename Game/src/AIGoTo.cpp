#include "AIGoTo.h"

AIGoTo::AIGoTo(float speed,int dest):speed(speed),dest(dest){
}

void AIGoTo::Update(GameObject &associated, float dt){

	associated.box.y+= speed*dt;

}

bool AIGoTo::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_TO);
}