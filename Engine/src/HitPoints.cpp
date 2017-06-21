#include "HitPoints.h"

HitPoints::HitPoints(uint hp) : healthBar(), healthColor(){
	this->hp = (int)hp;

}
HitPoints::~HitPoints(){

}


void HitPoints::Update(GameObject &associated, float dt){



}

bool HitPoints::Is(ComponentType type) const{
	return (ComponentType::HIT_POINTS == type);
}
int HitPoints::GetHp(){
	return hp;
}
void HitPoints::Damage(int damage){
	hp -= damage;
}

