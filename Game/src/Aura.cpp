#include "Aura.h"

Aura::Aura(GameObject &associated,
			Enemy::Event auraType,
			float auraRange,
			float timeBetweetNotifications,
			NearestGOFinder &finder)
	:associated(associated),
		auraType(auraType),
		auraRange(auraRange),
		timeBetweetNotifications(timeBetweetNotifications),
		finder(finder){
	if(Enemy::Event::SMOKE == auraType){
		
	}
	else if(Enemy::Event::STUN == auraType){
		
	}
	else if(Enemy::Event::HEALER == auraType){
		
	}
}

void Aura::Update(float dt){
	notificationTimer.Update(dt);
	if(notificationTimer.Get() > timeBetweetNotifications){
		notificationTimer.Restart();
		vector<GameObject *> *enemiesInRange= finder.FindNearestGOs(associated.box.Center(), "Enemies", auraRange);
		for(uint i=0; i< enemiesInRange->size(); i++){
			( (Enemy*)((*enemiesInRange)[i]) )->NotifyEvent(auraType);
		}
		delete enemiesInRange;
	}
}

void Aura::Render(void){
	Vec2 startPoint= associated.box;
	startPoint= startPoint - Vec2(sp.GetWidth()/2, sp.GetHeight()/2);
	sp.Render(Rect(startPoint.x, startPoint.y, sp.GetWidth(), sp.GetHeight()));
	startPoint= associated.box;
	startPoint= startPoint - Vec2(sp2.GetWidth()/2, sp2.GetHeight()/2);
	sp2.Render(Rect(startPoint.x, startPoint.y, sp2.GetWidth(), sp2.GetHeight()));
}

