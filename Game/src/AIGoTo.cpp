#include "AIGoTo.h"

AIGoTo::AIGoTo(float speed,int dest,GameObject &associated):speed(speed),dest(dest),associated(associated){
}

void AIGoTo::Update(float dt){

	associated.box.y+= speed*dt;

}

bool AIGoTo::Is(ComponentType type) const{
	return (type == ComponentType::AI_GO_TO);
}