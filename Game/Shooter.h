#ifndef SHOOTER_H
#define SHOOTER_H

#include "Component.h"
#include "GameObject.h"
#include "NearestGOFinder.h"
#include "Timer"

class Shooter : public Component
{
	public:
		Shooter(NearestGOFinder &finder,
				std::string targetType,
				float range,
				float betweetShootsTime,
				TargetPolicy policy,
				bool active);
		void Update(float dt)=0;
		bool Is(ComponentType type) const;
		enum TargetPolicy{
			ALWAYS_NEAREST,
			SHOOT_UNTIL_OUT_OF_RANGE
		};
	private:
		NearestGOFinder &finder;
		bool active;
		std::string targetType;
		float range;
		float betweetShootsTime;
		Timer timerBetweetShoots;
		GameObject *target;
		TargetPolicy policy;
};

#endif // SHOOTER_H
