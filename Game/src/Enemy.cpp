#include "Enemy.h"
#include "Camera.h"
#include "Error.h"
#include "AIGoDown.h"

#define ENEMY_MOVE_SPEED (30.)

Enemy::Enemy(Vec2 position, float lifeModifier ):sp("img/minion.png"), dead(false){
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
}
Enemy::~Enemy(){
	for(uint i =0; i < components.size(); i++){
		delete components[i];
	}
	components.clear();
}

void Enemy::Update(float dt){
	int forLimit= components.size();
	for(int i=0; i < forLimit; i++){
		components[i]->Update(*this, dt);
	}
}

void Enemy::Render(void){
	sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, 0, true);
}

bool Enemy::IsDead(void){
	return false;
}

void Enemy::RequestDelete(){
}

void Enemy::NotifyCollision(GameObject &object){
}

bool Enemy::Is(string type){
	return type == "Enemy";
}
Rect Enemy::GetWorldRenderedRect(void) const{
	Rect rect;
	rect.x= box.x-Camera::pos.x;
	rect.y= box.y-Camera::pos.y;
	rect.w= sp.GetWidth();
	rect.h= sp.GetHeight();
	
	rect = rect*Camera::GetZoom();
	
	return rect+Camera::pos;
}
