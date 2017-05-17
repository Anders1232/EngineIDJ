#include "Face.h"
#include "DragAndDrop.h"
#include "Camera.h"


Face::Face(float x, float y, Vec2 tileSize, TileMap *tileMap)
	:sp("img/penguinface.png"){
	box.x= x;
	box.y= y;
	sp.ScaleX(tileSize.x/sp.GetWidth());
	sp.ScaleY(tileSize.y/sp.GetHeight());
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	components.emplace_back( new DragAndDrop(tileMap, true) );
}
void Face::Damage(int damage)
{
	hitpoints = hitpoints - damage;
}

void Face::Update(float dt )
{
	for(unsigned int count =0; count < components.size(); count++)
	{
		components[count]->Update(*this);
	}
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
	
	return rect+Camera::pos;
}

bool Face::Is(string type){
	return type == "Face";
}


Face::~Face(){

}
