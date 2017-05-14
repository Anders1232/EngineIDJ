#include "Face.h"
#include "DragAndDrop.h"
#include "Camera.h"
typedef unsigned int uint;

Face::Face(float x, float y){
	sp.Open("img/penguinface.png");
	box.x = x - sp.GetWidth()/2; 
	box.y = y - sp.GetHeight()/2;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	components.emplace_back( new DragAndDrop(true) );
}
void Face::Damage(int damage)
{
	hitpoints = hitpoints - damage;
}

void Face::Update(float dt )
{
	for(uint count =0; count < components.size(); count++)
	{
		components[count]->Update(*this);
	}
}
void Face::Render()
{
	//Centraliza mas da problema de ele voar ate o 0,0 depois de posicionado
	//box.x = box.x - sp.GetWidth()/2;
	//box.y = box.y - sp.GetHeight()/2;
	sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y);

}
bool Face::IsDead(void)
{
	if(hitpoints<=0)
		return true;
	else
		return false;
}

void Face::NotifyCollision(GameObject &other){

}

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
	for(uint count =0; count < components.size(); count++)
	{
		// deleting object of abstract class type ‘Component’ which has non-virtual destructor will cause undefined behaviour
		//delete components[count];
	}
	

}
