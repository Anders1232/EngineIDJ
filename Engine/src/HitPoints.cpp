#include "HitPoints.h"

HitPoints::HitPoints(uint hp) : healthBar("img/effect/health_bar.png"), healthColor(){
	this->hp = (int)hp;

}
HitPoints::~HitPoints(){

}


void HitPoints::Update(GameObject &associated, float dt){
	

}

void HitPoints::Render(GameObject &associated){
	healthBar.Render(associated.box);
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

