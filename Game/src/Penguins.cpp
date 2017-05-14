#include "Penguins.h"
#include "InputManager.h"
#include "Camera.h"
#include "Error.h"
#include "Bullet.h"
#include "Game.h"
#include "Animation.h"
#include "Sound.h"

#define PENGUIM_LINEAR_SPEED (150)
#define PENGUIM_CANNON_ANGLE (20)
#define PENGUIM_HP (10000)
#define PENGUIM_MAX_SPEED (200.)
#define PENGUIM_ACELERACAO (1.1)
#define PENGUIM_VEC_ANGULAR (2.)
#define PENGUIM_BULLET_SPEED (180)
#define PENGUIM_BULLET_FRAMETIME (0.5)
//#define PENGUIM_BULLET_MAX_DISTANCE (360)
#define PENGUIM_BULLET_MAX_DISTANCE (PENGUIM_BULLET_FRAME_COUNT*PENGUIM_BULLET_FRAMETIME*PENGUIM_BULLET_SPEED)
#define PENGUIM_BULLET_FRAME_COUNT (4)
#define PENGUIN_CANNON_LENGHT (50)
#define PENGUIM_DAMAGE_PER_BULLET (15)
#define PENGUIM_BULLET_COODOWN (1./3.)


Penguins* Penguins::player= nullptr;

Penguins::Penguins(float x, float y):GameObject(),bodySP("img/penguin.png"), cannonSp("img/cubngun.png"), speed(), linearSpeed(PENGUIM_LINEAR_SPEED), cannonAngle(PENGUIM_CANNON_ANGLE), hp(PENGUIM_HP), bulletsTimer()
{
	player= this;
	box.x= x;
	box.y= y;
	box.w= bodySP.GetWidth();
	box.h= bodySP.GetHeight();
	Camera::Follow(this);
}

Penguins::~Penguins()
{
	player = nullptr;
	Camera::Unfollow();
}

void Penguins::Update(float dt)
{
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.IsKeyDown('w') || inputManager.IsKeyDown('W'))
	{
		speed+= Vec2(1, 0) + speed*PENGUIM_ACELERACAO*dt;//se o penguim não se mover olhar aqui
		if(PENGUIM_MAX_SPEED < speed.Magnitude() )
		{
			speed.Normalize();
			speed= speed * PENGUIM_MAX_SPEED;
		}
	}
	if(inputManager.IsKeyDown('s') || inputManager.IsKeyDown('S'))
	{
		speed-= Vec2(1, 0) + speed*PENGUIM_ACELERACAO*dt;//se o penguim não se mover olhar aqui
		if(PENGUIM_MAX_SPEED < speed.Magnitude() )
		{
			speed.Normalize();
			speed= speed * PENGUIM_MAX_SPEED;
		}
	}
	if(inputManager.IsKeyDown('a')|| inputManager.IsKeyDown('A'))
	{
//		TEMP_REPORT_I_WAS_HERE;
		rotation-= PENGUIM_VEC_ANGULAR*dt;
	}
	if(inputManager.IsKeyDown('d')|| inputManager.IsKeyDown('D'))
	{
		rotation+= PENGUIM_VEC_ANGULAR*dt;
	}
	box= box + speed.Rotate(rotation)*dt;
	cannonAngle= (inputManager.GetMousePos()-(box.Center()-Camera::pos)*Camera::GetZoom()).Inclination()*CONVERSAO_GRAUS_RADIANOS;
	CheckMapLimits();

	bulletsTimer.Update(dt);
	if(inputManager.IsMouseDown(LEFT_MOUSE_BUTTON))
	{
		if(bulletsTimer.Get() > PENGUIM_BULLET_COODOWN)
		{
			bulletsTimer.Restart();
			Shoot();
		}
	}
}
void Penguins::Render(void)
{
	bodySP.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation*CONVERSAO_GRAUS_RADIANOS, true);
	cannonSp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, cannonAngle, true);
}

Rect Penguins::GetWorldRenderedRect(void) const
{
	Rect ret;
	float bodyValue, cannonValue;

	bodyValue= box.x-Camera::pos.x;
	cannonValue= box.x-Camera::pos.x;
	ret.x= (bodyValue < cannonValue)? bodyValue: cannonValue;

	bodyValue= box.y-Camera::pos.y;
	cannonValue= box.y-Camera::pos.y;
	ret.y= (bodyValue < cannonValue)? bodyValue: cannonValue;

	bodyValue= bodySP.GetWidth();
	cannonValue= cannonSp.GetWidth();
	ret.w= (bodyValue > cannonValue)? bodyValue: cannonValue;

	bodyValue= bodySP.GetHeight();
	cannonValue= cannonSp.GetHeight();
	ret.h= (bodyValue > cannonValue)? bodyValue: cannonValue;

	ret= ret* Camera::GetZoom();

	return ret;
}

bool Penguins::IsDead(void)
{
	return (0>=hp);
}
void Penguins::Shoot(void)
{
	REPORT_I_WAS_HERE;
	Bullet* bullet= new Bullet(
				box.Center().x-Camera::pos.x+Vec2::FromPolarCoord(PENGUIN_CANNON_LENGHT, cannonAngle/CONVERSAO_GRAUS_RADIANOS).x,
				box.Center().y-Camera::pos.y+Vec2::FromPolarCoord(PENGUIN_CANNON_LENGHT, cannonAngle/CONVERSAO_GRAUS_RADIANOS).y,
				cannonAngle/CONVERSAO_GRAUS_RADIANOS,
				PENGUIM_BULLET_SPEED,
				PENGUIM_BULLET_MAX_DISTANCE,
				PENGUIM_BULLET_FRAMETIME,
				PENGUIM_BULLET_FRAME_COUNT,
				"img/penguinbullet.png",
				false
			);
	REPORT_I_WAS_HERE;
	Game::GetInstance().GetCurrentState().AddObject(bullet);
	REPORT_I_WAS_HERE;
}

void Penguins::NotifyCollision(GameObject &other)
{
	if(other.Is("Bullet"))
	{
		if(((Bullet&)other).TargetsPlayer())
		{
			hp-= PENGUIM_DAMAGE_PER_BULLET;
			if(IsDead())
			{
				Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x, box.y, rotation, "img/penguindeath.png", 5, 0.25, true));
				Sound explosionSound("audio/boom.wav");
				explosionSound.Play(1);
			}

		}
	}
}
bool Penguins::Is(string type)
{
	return type=="Penguins";
}

void Penguins::CheckMapLimits(void)
{
	Vec2 pos= box.Center();
	Vec2 diff= box-box.Center();
	if(PENGUIM_MAX_BOX_X < pos.x )
	{
		box.x= PENGUIM_MAX_BOX_X+diff.x;
	}
	else if(PENGUIM_MIN_BOX_X > pos.x)
	{
		box.x= PENGUIM_MIN_BOX_X+diff.x;
	}
	if(PENGUIM_MAX_BOX_Y < pos.y )
	{
		box.y= PENGUIM_MAX_BOX_Y+diff.y;
	}
	else if(PENGUIM_MIN_BOX_Y > pos.y)
	{
		box.y= PENGUIM_MIN_BOX_Y+diff.y;
	}
}


