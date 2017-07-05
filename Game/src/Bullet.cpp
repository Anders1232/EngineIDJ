#include "Bullet.h"
#include "Camera.h"
#include "Error.h"

Bullet::Bullet(float x,float y,float angle,float speed,float maxDistance,std::string sprite,std::string targetType,float frameTime,int frameCount)
: sp(sprite,false,frameTime, frameCount),targetType(targetType){
	box.x= x;
	box.y= y;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	rotation= angle;
	this->speed= Vec2::FromPolarCoord(speed, angle);
	distanceLeft= maxDistance;
}

void Bullet::Update(float dt){
	box= box + speed*dt;
	distanceLeft-= speed.Magnitude()*dt;
	sp.Update(dt);
}
void Bullet::Render(void){
	sp.Render(Rect(box.x,box.y,sp.GetWidth(),sp.GetHeight()),rotation,false);
}
bool Bullet::IsDead(void){
	return (distanceLeft<=0);
}

Bullet::~Bullet(){
}

void Bullet::NotifyCollision(GameObject &other){
	if(other.Is(targetType)){
		distanceLeft= 0;
		std::cout << "Explodeeeeeeeee" << std::endl;
		Game::GetInstance().GetCurrentState().AddObject(new Animation(box.Center().x,box.Center().x,rotation,"img/explosion.png",4,0.1,true));
	}
}

bool Bullet::Is(string type){
	return type=="Bullet";
}
