
#include "Face.h"


Face::Face(float x, float y){

	componentArray.emplace_back( new Dragable() )
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