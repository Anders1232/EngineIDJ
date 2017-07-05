#ifndef SHOOTER_H
#define SHOOTER_H

#include <string>
#include "Component.h"
#include "GameObject.h"
#include "NearestGOFinder.h"
#include "Timer"

class Shooter : public Component
{
	public:
		Shooter(GameObject &associated,
				NearestGOFinder &finder,
				std::string targetType,
				float range,
				float betweetShootsTime,
				TargetPolicy policy,
				bool active,
				float bulletSpeed,
				float bulletMaxDistance,
				std::string bulletSprite);
		void Update(float dt)=0;
		bool Is(ComponentType type) const;
		enum TargetPolicy{
			ALWAYS_NEAREST,
			SHOOT_UNTIL_OUT_OF_RANGE
		};
	private:
		GameObject &associated;
		NearestGOFinder &finder;
		bool active;
		std::string targetType;
		float range;
		float betweetShootsTime;
		Timer timerBetweetShoots;
		GameObject *target;
		TargetPolicy policy;
		
		//agora os argumentos que precisam ser enviados ao construtor de bullet
		float bulletSpeed;
		float bulletMaxDistance;
		std::string bulletSprite;
};

#endif // SHOOTER_H
