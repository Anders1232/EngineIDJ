#include "Enemy.h"
#include "Camera.h"
#include "Error.h"


Enemy::Enemy(int wave ){
	hp = BASE_HIT_POINTS + (DIFICULTY_CONSTANT * wave);
	//this->type = enemyType;

}
Enemy::~Enemy(){

}
void Enemy::Update(float dt){

}
void Enemy::Render(void){

}
bool Enemy::IsDead(void){
	if( hp <= 0 )
		return true;
	else
		return false;
}
void Enemy::RequestDelete(){

}
void Enemy::NotifyCollision(GameObject *object){

}
bool Enemy::Is(string type){
	return type == "Enemy";
}
Rect Enemy::GetWorldRenderedRect(void){
	Rect rect;
	rect.x= box.x-Camera::pos.x;
	rect.y= box.y-Camera::pos.y;
	rect.w= sp.GetWidth();
	rect.h= sp.GetHeight();
	
	rect = rect*Camera::GetZoom();
	
	return rect+Camera::pos;
}
