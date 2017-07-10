#include "HitPoints.h"

HitPoints::HitPoints(uint hp,GameObject &associated, float scaleX)
		: healthBar("img/effect/health_bar.png")
		, healthColor("img/effect/health_color.png")
		, associated(associated) {
			
	this->hp = (int)hp;
	maxHp = (int)hp;
	healthBar.SetScaleX(scaleX);
	healthColor.SetScaleX(scaleX);
}

HitPoints::~HitPoints(){
}


void HitPoints::Update(float dt){
	Color& c = healthColor.colorMultiplier;
	c.r = 255*(1-(float)hp/maxHp);
	c.b = 0;
	c.g = 255*((float)hp/maxHp);
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

