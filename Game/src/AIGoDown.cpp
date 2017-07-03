#include "AIGoDown.h"

AIGoDown::AIGoDown(float speed, GameObject &associated):speed(speed),associated(associated){
}

void AIGoDown::Update(float dt){
	associated.box.y+= speed*dt;
}

bool AIGoDown::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_DOWN);
}
