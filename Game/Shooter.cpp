#include "Shooter.h"
#include "Game.h"
#include "Bullet.h"

Shooter::Shooter(GameObject &associated,
		NearestGOFinder &finder,
		std::string targetType,
		float range,
		float betweetShootsTime,
		TargetPolicy policy,
		bool active,
		float bulletSpeed,
		float bulletMaxDistance
		std::string bulletSprite):
	associated(associated),
	finder(finder),
	active(active),
	targetType(targetType),
	range(range),
	betweetShootsTime(betweetShootsTime),
	timerBetweetShoots(),
	target(nullptr),
	policy(policy),
	bulletSpeed(bulletSpeed),
	bulletMaxDistance(bulletMaxDistance)
	bulletSprite(bulletSprite){
}

bool Shooter::Is(ComponentType type) const{
	return ComponentType::SHOOTER == type;
}

void Shooter::Update(float dt){
	if(active){
		timerBetweetShoots.Update(dt);
		if(timerBetweetShoots.Get() < betweetShootsTime){
			timerBetweetShoots.Reset();
			if(nullptr == target || TargetPolicy::ALWAYS_NEAREST == policy){
				target= finder.FindNearestGO(associated.box.Center(), targetType, range);
			}
			//supoe-se aqui que já existe um algo e a políica de tipo é SHOOT_UNTIL_OUT_OF_RANGE
			else if( (target->box.Center()-associated.box.Center() ).Magnitude() > range){
				target= finder.FindNearestGO(associated.box.Center(), targetType, range);
			}
			if(nullptr!= target){
				float angle= (associated.box.Center()-target->box.Center() ).Inclination();
				Game::GetInstance().GetCurrentState().AddObject(new Bullet(associated.x, associated.y, inclination, bulletSpeed, bulletMaxDistance, bulletSprite, targetType));
			}
		}
	}
}

void Shooter::SetActive(bool active){
	this->active= active;
}

