#include "Face.h"
#include "DragAndDrop.h"
#include "Camera.h"


Face::Face(float x, float y){
	sp.Open("img/penguinface.png");
	box.x= x;
	box.y= y;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	components.emplace_back( new DragAndDrop() );
}
void Face::Damage(int damage)
{
	hitpoints = hitpoints - damage;
}

void Face::Update(float dt )
{

}
void Face::Render()
{
	sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y);

}
bool Face::IsDead(void)
{
	if(hitpoints<=0)
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

bool Face::Is(string type){
	return type == "Face";
}


Face::~Face(){

}
