#include "HitPoints.h"


HitPoints::HitPoints(uint hp,GameObject &associated, float scaleX) : healthBar("img/effect/health_bar.png"), healthColor("img/effect/health_color.png"),associated(associated){
	this->hp = (int)hp;
	healthBar.SetScaleX(scaleX);
	healthColor.SetScaleX(scaleX);
}

HitPoints::~HitPoints(){
}


void HitPoints::Update(float dt){
}

void HitPoints::Render(){
	healthBar.Render(associated.box);
	healthColor.Render(associated.box);
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
void HitPoints::RequestDelete(void){

	hp = 0;

}

