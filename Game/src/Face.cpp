#include "Face.h"
#include "DragAndDrop.h"
#include "Camera.h"
#include "Error.h"

typedef unsigned int uint;


Face::Face(float x, float y, Vec2 tileSize, TileMap *tileMap)
	:sp("img/tower/torre_fumaca.png"),
	hitpoints(FACE_HP){
		
	box.x= x;
	box.y= y;
	sp.ScaleX(tileSize.x/sp.GetWidth()*2);
	sp.ScaleY(tileSize.y/sp.GetHeight()*2);
	sp.colorMultiplier = Color( 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX );
	sp.alpha = 255*(float)rand()/RAND_MAX;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
}

void Face::Damage(int damage){
	hitpoints = hitpoints - damage;
}

void Face::Update(float dt ){
	for(uint count =0; count < components.size(); count++){
		components[count]->Update(*this, dt);
	}
}
void Face::Render(){
	sp.Render((box.x-Camera::pos.x)*Camera::GetZoom(), (box.y-Camera::pos.y)*Camera::GetZoom(), 0, true);

}
bool Face::IsDead(void){
	if(hitpoints<=0)
		return true;
	else
		return false;
}

void Face::RequestDelete(void){
	hitpoints= 0;
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
	
	return rect+Camera::pos;
}

bool Face::Is(string type){
	return type == "Face";
}


Face::~Face(){
	for(uint i=0; i < components.size(); i++){
		delete components[i];
	}
	components.clear();
}
