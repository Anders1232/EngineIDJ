#include "HitPoints.h"

HitPoints::HitPoints(float hp) : healthBar(), healthColor(){
	this->hp = hp;

}
HitPoints::~HitPoints(){

}
void HitPoints::Update(GameObject &associated){

}
bool HitPoints::Is(ComponentType type) const{
	return (ComponentType::HIT_POINTS == type);
}