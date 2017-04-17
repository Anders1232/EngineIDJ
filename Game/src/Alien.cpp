#include "Alien.h"
#include "Camera.h"
//#include "InputManager.h"
#include "Error.h"
#include "climits"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Penguins.h"
#include "Sound.h"

#define DISTANCE_NEAR_ENOUGH 10
#define HP_INICIAL (30)
#define ALIEN_DAMAGE_PER_BULLET (13)
#define ALIEN_RESTING_COOLDOWN (2)

int Alien::alienCount=0;

Alien::Alien(float x, float y, int nMinions) : GameObject(), state(RESTING), sp("img/alien.png"), hp(HP_INICIAL), alienRestingCooldown(CalculateRestingCooldown()), lastDistance(0)
{
	box.x= x;
	box.y= y;
	box.w= sp.GetWidth();
	box.h= sp.GetHeight();
	for(int count=0; count < nMinions; count++)
	{
//		std::cout << WHERE << "  " << count*360/nMinions << endl;
		minionArray.emplace_back(Minion(this, count*360/nMinions));
	}
	alienCount++;
}
Alien::~Alien(void)
{
	minionArray.clear();
	alienCount--;
}

void Alien::Update(float dt)
{
	if(nullptr ==  Penguins::player)
	{
		return;
	}
	if(RESTING== state)
	{
		restTimer.Update(dt);
		if(alienRestingCooldown < restTimer.Get())
		{//muda de estado
			destination= Penguins::player->box.Center();
			speed= Penguins::player->box.Center()-box.Center();
			lastDistance= speed.Magnitude();
			speed.Normalize();
			speed= speed*ALIEN_MOVE_SPEED;
			state= MOVING;
		}
	}
	else if(MOVING == state)
	{
//		if( DISTANCE_NEAR_ENOUGH > ( (destination-box.Center() ).Magnitude() ) )
		if( lastDistance < ( (destination-box.Center() ).Magnitude() )  ||  DISTANCE_NEAR_ENOUGH > ( (destination-box.Center() ).Magnitude() ) )
//		if( lastDistance < ( (destination-box.Center() ).Magnitude() ) )
		{
//			lastDistance= (destination-box.Center() ).Magnitude();
			box= box + destination-box.Center();
			Vec2 targetPos= Penguins::player->box.Center();
			minionArray[GetNearestMinion(targetPos)].Shoot(targetPos);
			restTimer.Restart();
			alienRestingCooldown= CalculateRestingCooldown();
			state= RESTING;
		}
		else
		{
			lastDistance= (destination-box.Center() ).Magnitude();
			box= box + speed*dt;
		}
	}
	else
	{
		std::cout << WHERE << " Nao era pra chegar aqui...\n";
	}
//	TEMP_REPORT_I_WAS_HERE;
	for(unsigned int count=0; count < minionArray.size(); count++)
	{
		minionArray[count].Update(dt);
	}
	rotation-= dt* CONVERSAO_GRAUS_RADIANOS/6.;
}
void Alien::Render(void)
{
	sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation, true);
	for(unsigned int count=0; count < minionArray.size(); count++)
	{
		minionArray[count].Render();
	}
}
bool Alien::IsDead(void)
{
	return (0 >=hp);
}

bool Alien::Is(string type)
{
	return type == "Alien";
}

void Alien::NotifyCollision(GameObject &other)
{
	if(other.Is("Bullet"))
	{
		if( !( ( (Bullet&)other).TargetsPlayer() ) )
		{
			hp-= ALIEN_DAMAGE_PER_BULLET;
			if(IsDead())
			{
				Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x, box.y, rotation, "img/aliendeath.png", 4, 0.25, true));
				Sound explosionSound("audio/boom.wav");
				explosionSound.Play(1);
			}
		}
	}
}

int Alien::GetNearestMinion(Vec2 targetPos)
{
	int nearestAlien=0;
	float nearestDistance= (targetPos - minionArray[0].box.Center()).Magnitude();
	nearestDistance= (nearestDistance >0)?nearestDistance: -nearestDistance;
	for(unsigned int count =1; count < minionArray.size(); count++)
	{
		float candidateDistance= (targetPos - minionArray[count].box).Magnitude();
		candidateDistance= (candidateDistance >0)?candidateDistance: -candidateDistance;
		if(candidateDistance < nearestDistance)
		{
			nearestAlien=count;
		}
	}
		return nearestAlien;
}

float Alien::CalculateRestingCooldown(void)
{
	return ALIEN_RESTING_COOLDOWN* 1+( ( ( (float)(rand()%101) )/100-0.5) );
}



