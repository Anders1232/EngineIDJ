#include "HitPoints.h"

HitPoints::HitPoints(uint hp) : healthBar(), healthColor(){
	this->hp = (int)hp;

}
HitPoints::~HitPoints(){

}
void HitPoints::Update(GameObject &associated, float dt){

	
	if(hp <= 0){
		associated.NotifyDeath();
	}

}
bool HitPoints::Is(ComponentType type) const{
	return (ComponentType::HIT_POINTS == type);
}
