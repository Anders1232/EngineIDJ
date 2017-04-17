#include "Bullet.h"
#include "Camera.h"
#include "Error.h"

Bullet::Bullet(float x,
		float y,
		float angle,
		float speed,
		float maxDistance,
		float frameTime,
		int frameCount,
		string sprite,
		bool targetsPlayer
): GameObject(), sp(sprite, frameTime, frameCount)
{
	box.x= Camera::pos.x+x -sp.GetWidth()/2;
	box.y= Camera::pos.y+y -sp.GetHeight()/2;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	rotation= angle*CONVERSAO_GRAUS_RADIANOS;
	this->speed= Vec2::FromPolarCoord(speed, angle);
	distanceLeft= maxDistance;
	this->targetsPlayer= targetsPlayer;
}

void Bullet::Update(float dt)
{
	box= box + speed*dt;
	distanceLeft-= speed.Magnitude()*dt;
	sp.Update(dt);
}
void Bullet::Render(void)
{
//	std::cout << WHERE << " rotation= " <<rotation <<endl;
	sp.Render(box.x- Camera::pos.x, box.y- Camera::pos.y, rotation, true);
}
bool Bullet::IsDead(void)
{
	return (distanceLeft<=0);
}

Bullet::~Bullet()
{}

void Bullet::NotifyCollision(GameObject &other)
{
	if( (other.Is("Penguins") && targetsPlayer) || (other.Is("Alien") && !targetsPlayer) || (other.Is("Minion") && !targetsPlayer) )
	{
		distanceLeft= 0;
	}
}
bool Bullet::Is(string type)
{
	return type=="Bullet";
}
bool Bullet::TargetsPlayer(void) const
{
	return targetsPlayer;
}


