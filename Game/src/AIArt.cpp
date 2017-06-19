#include "AIArt.h"

//AIState{WALKING,WAITING,FINDINGHEALTH,STUNNED};
//AIEvent{PATH_BLOCKED,PATH_FREE,FOUNDHEALTH,STUN,NOT_STUN}; 

AIArt::AIArt(float speed,int dest):speed(speed),destTile(dest){

	dfa[AIState::WALKING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING][AIEvent::PATH_BLOCKED] = AIState::WAITING;

	dfa[AIState::WAITING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WAITING][AIEvent::PATH_FREE] = AIState::WALKING;

	dfa[AIState::STUNNED][AIEvent::NOT_STUN] = AIState::WALKING;
	dfa[AIState::STUNNED][AIEvent::PATH_BLOCKED] = AIState::WAITING;

	actualState = AIState::WAITING;
}

void AIArt::Compute(){}

void AIArt::Update(GameObject &associated, float dt){

	associated.box.y+= speed*dt;

}

bool AIArt::Is(ComponentType type) const{
	return (type == ComponentType::AI_ART);
}
