#include "Face.h"
#include "DragAndDrop.h"


Face::Face(float x, float y){

	components.emplace_back( new DragAndDrop() );
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
	return false;
}

Face::~Face(){

}
