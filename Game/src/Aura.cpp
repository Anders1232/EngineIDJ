#include "Aura.h"

Aura::Aura(GameObject &associated,
			Enemy::Event auraType,
			float auraRange,
			float timeBetweetNotifications,
			NearestGOFinder &finder,
			std::string targetType)
	:associated(associated),
		auraType(auraType),
		auraRange(auraRange),
		timeBetweetNotifications(timeBetweetNotifications),
		finder(finder),
		targetType(targetType){
	if(Enemy::Event::SMOKE == auraType){
		sp= Sprite("img/tower/Fumaça_spritesheet.png", false, 0.3f, 8);
		sp.colorMultiplier= Color(179, 150, 120);
		sp2= Sprite("img/tower/Fumaça_spritesheet.png", false, 0.3f, 8);
		sp2.colorMultiplier= Color(179, 150, 120);
		sp2.SetFrame(3);
	}
	else if(Enemy::Event::STUN == auraType){
		sp= Sprite("img/SpriteSheets/stun_spritesheet.png", false, 0.3f, 7);
		sp2= Sprite("img/SpriteSheets/stun_spritesheet.png", false, 0.3f, 7);
		sp2.SetFrame(3);
	}
	else if(Enemy::Event::HEALER == auraType){
		sp= Sprite("img/SpriteSheets/aura_spritesheet.png", false, 0.3f, 7);
	}
	sp.ScaleX(auraRange/(float)sp.GetWidth());
	sp.ScaleY(auraRange/(float)sp.GetHeight());
	if(Enemy::Event::HEALER != auraType){
		sp2.ScaleX(auraRange/(float)sp2.GetWidth());
		sp2.ScaleY(auraRange/(float)sp2.GetHeight());
	}
	sp.colorMultiplier.a= 115;
	sp2.colorMultiplier.a= 115;
}

void Aura::Update(float dt){
	sp.Update(dt);
	sp2.Update(dt);
	notificationTimer.Update(dt);
	if(notificationTimer.Get() > timeBetweetNotifications){
		notificationTimer.Restart();
		vector<GameObject *> *enemiesInRange= finder.FindNearestGOs(associated.box.Center(), targetType, auraRange);
		for(uint i=0; i< enemiesInRange->size(); i++){
			( (Enemy*)((*enemiesInRange)[i]) )->NotifyEvent(auraType);
		}
		delete enemiesInRange;
	}
}

void Aura::Render(void){
	Vec2 startPoint= associated.box;
	startPoint= startPoint - Vec2((-associated.box.w + sp.GetWidth())/2, (-associated.box.w + sp.GetHeight())/2);
	sp.Render(Rect(startPoint.x, startPoint.y, sp.GetWidth(), sp.GetHeight()));
	if(Enemy::Event::HEALER != auraType){
		startPoint= associated.box;
		startPoint= startPoint -  Vec2((-associated.box.w + sp.GetWidth())/2, (-associated.box.w + sp.GetHeight())/2);
		sp2.Render(Rect(startPoint.x, startPoint.y, sp2.GetWidth(), sp2.GetHeight()));
	}
}

bool Aura::Is(ComponentType type) const{
	if(Enemy::Event::SMOKE == auraType){
		return ComponentType::SLOW_AURA== type;
	}
	else if(Enemy::Event::STUN == auraType){
		return ComponentType::STUN_AURA == type;
	}
	else if(Enemy::Event::HEALER == auraType){
		return ComponentType::HEAL_AURA == type;
	}
	else{
		Error("\t Should not get here!");
	}
}
