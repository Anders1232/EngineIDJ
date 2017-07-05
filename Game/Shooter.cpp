#include "Shooter.h"

Shooter::Shooter(NearestGOFinder &finder,
		std::string targetType,
		float range,
		float betweetShootsTime,
		TargetPolicy policy,
		bool active):
	finder(finder),
	active(active),
	targetType(targetType),
	range(range),
	betweetShootsTime(betweetShootsTime),
	timerBetweetShoots(),
	target(nullptr),
	policy(policy){
}

bool Shooter::Is(ComponentType type) const{
	return ComponentType::SHOOTER == type;
}

