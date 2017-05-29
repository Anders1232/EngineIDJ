#include "Wave.h"

Wave::Wave(){

}
Wave::~Wave(){

}

void Wave::Update(float dt){

}
void Wave::Render(void){

}
bool Wave::IsDead(void){
	return false;
}
void Wave::RequestDelete(){

}
void Wave::NotifyCollision(GameObject *object){

}
bool Wave::Is(string type){
	return false;
}
Rect Wave::GetWorldRenderedRect(void){
	Rect rect;
	rect.x= 0;
	rect.y= 0;
	rect.w= 0;
	rect.h= 0;
	return rect;
}