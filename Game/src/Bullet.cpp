#include "Bullet.h"
#include "Camera.h"
#include "Error.h"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, std::string sprite, std::string targetType, float scale, float frameTime, int frameCount, bool isBomb)
: sp(sprite,false,frameTime, frameCount),targetType(targetType), isBomb(isBomb){
	sp.SetScale(scale);
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
	sp.Render(Rect(box.x,box.y,sp.GetWidth(),sp.GetHeight()),rotation*CONVERSAO_GRAUS_RADIANOS);
}

bool Bullet::IsDead(void){
	return (distanceLeft<=0);
}

Bullet::~Bullet(){
}

void Bullet::NotifyCollision(GameObject &other){
	if(other.Is(targetType)){
		distanceLeft= 0;
		if(other.Is("Tower")){
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
		}
		else if(other.Is("BOMB")){
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/anti-bomba_ativ_spritesheet.png",11,0.1,true));
			other.RequestDelete();
		}
		else{
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"./img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
		}
		RequestDelete();
	}
}

bool Bullet::Is(string type){
	if(isBomb){
		return "BOMB" ==  type;
	}
	else{
		return "Bullet" == type;
	};
}

std::string Bullet::getTargetType(){
	return targetType;
}
