
#include "Face.h"


Face::Face(float x, float y){

	componentArray.emplace_back( new DragAndDrop() );
}
void Face::Damage(int damage)
{

}

void Face::Update(float dt )
{

}
void Face::Render()
{

}
bool Face::isDead()
{
	if(hp<=0)
		return true;
	else
		return false;
}

void Face::NotifyCollision(GameObject &other){}

Rect Face::GetWorldRenderedRect( ) const{
	Rect rect;
	rect.x= box.x-Camera::pos.x;
	rect.y= box.y-Camera::pos.y;
	rect.w= sp.GetWidth();
	rect.h= sp.GetHeight();
	
	rect = rect*Camera::GetZoom();
	
	return rect;
}


Face::~Face(){

}