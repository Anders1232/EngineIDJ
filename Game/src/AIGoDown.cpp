#include "AIGoDown.h"

AIGoDown::AIGoDown(float speed):speed(speed){
}

void AIGoDown::Update(GameObject &associated, float dt){
	associated.box.y+= speed*dt;
}

bool AIGoDown::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_DOWN);
}
