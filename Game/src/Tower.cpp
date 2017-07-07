#include "Tower.h"

#include "Camera.h"
#include "DragAndDrop.h"
#include "Error.h"
#include "Shooter.h"
#include "Game.h"
#include "StageState.h"
#include "Aura.h"

#define SORTEAR_TORRES

Tower::Tower(TowerType type, Vec2 pos, Vec2 tileSize, int hp)
		: sp(type == TowerType::SMOKE ? "img/tower/torre_fumaca.png" :
			type == TowerType::ANTIBOMB ? "img/tower/torre-anti-bomba.png" :
			type == TowerType::STUN ? "img/tower/torrestun.png" :
			type == TowerType::SHOCK ? "img/tower/torrechoque_lvl1.png" :
			"",
			true){
	box.x = pos.x;
	box.y = pos.y;
	sp.ScaleX(2*tileSize.x/sp.GetWidth());
	sp.ScaleY(4*tileSize.y/sp.GetHeight());
	//sp.colorMultiplier = Color( 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 127 + 127*(float)rand()/RAND_MAX );
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	StageState& stageState= (StageState&)Game::GetInstance().GetCurrentState();

#ifdef SORTEAR_TORRES
	int sorteio = rand()%4;
	if(0 == sorteio){
		switch(type){
			case TowerType::SMOKE:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/spritesheets/fumaça_spritesheet.png", 8, 1));
				break;
			case TowerType::ANTIBOMB:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/spritesheets/anti-bomba_ativ_spritesheet.png", 11, 1));
				break;
			case TowerType::STUN:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/spritesheets/stun_spritesheet.png", 8, 1));
				break;
			case TowerType::SHOCK:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/spritesheets/bullet_choquelvl1.png", 4, 1));
				break;
		}
	}
	else if (1 == sorteio){
		AddComponent(new Aura(*this, Enemy::Event::SMOKE, 300, 7.0, (NearestGOFinder&)stageState, "Enemy"));
	}
	else if (2 == sorteio){
		AddComponent(new Aura(*this, Enemy::Event::SMOKE, 300, 1.0, (NearestGOFinder&)stageState, "Enemy"));
	}
	else{
		AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 1000, 3.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 3000, "img/SpriteSheets/anti-bomba_idle.png", 5, 2.0));
		switch(type){
			case TowerType::SMOKE:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 1000, 3.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 3000, "img/spritesheets/fumaça_spritesheet.png", 8, 1));
				break;
			case TowerType::ANTIBOMB:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 1000, 3.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 3000, "img/spritesheets/anti-bomba_ativ_spritesheet.png", 11, 1));
				break;
			case TowerType::STUN:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 1000, 3.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 3000, "img/spritesheets/stun_spritesheet.png", 8, 1));
				break;
			case TowerType::SHOCK:
				AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 1000, 3.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 3000, "img/spritesheets/bullet_choquelvl1.png", 4, 1));
				break;
		}
	}
#else
	AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/minionbullet1.png",3,2));
#endif

	hitpoints = new HitPoints(hp,*this);
	components.push_back(hitpoints);
}

Tower::~Tower() {
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
}

void Tower::Damage(int damage) {
	hitpoints->Damage(damage);
}

void Tower::Update(float dt ) {
	for(uint count = 0; count < components.size(); count++) {
		components[count]->Update(dt);
	}
}

void Tower::Render(void) {
	sp.Render(box);
	for(uint i=0; i< components.size(); i++){
		(components[i])->Render();
	}
}

bool Tower::IsDead(void) {
	 return 0 >= hitpoints->GetHp();
}

void Tower::RequestDelete(void) {
	hitpoints->RequestDelete();
}

Rect Tower::GetWorldRenderedRect() const {
	return Camera::WorldToScreen(box);
}

bool Tower::Is(string type) {
	return "Tower" == type;
}

void Tower::NotifyCollision(GameObject &object){

	if(object.Is("Bullet")){
		if(((Bullet&)object).getTargetType() == "Tower"){
			hitpoints->Damage(TOWER_BULLET_DAMAGE);
		}
	}
}
