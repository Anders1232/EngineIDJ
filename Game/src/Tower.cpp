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
		: sp(type == TowerType::SMOKE ? "img/SpriteSheets/torre_fumaca.png" :
			type == TowerType::ANTIBOMB ? "img/SpriteSheets/anti-bomba.png" :
			type == TowerType::STUN ? "img/SpriteSheets/torrestun.png" :
			type == TowerType::SHOCK ? "img/SpriteSheets/torrechoque_lvl1.png" :
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

	switch(type){
		case TowerType::SMOKE:
			AddComponent(new Aura(*this, Enemy::Event::SMOKE, 800, 7.0, (NearestGOFinder&)stageState, "Enemy"));
			break;
		case TowerType::ANTIBOMB:
            sp.SetFrameCount(8);
            sp.SetFrameTime(0.5);
			AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/SpriteSheets/anti-bomba_ativ_spritesheet.png", 11, 1));
			break;
		case TowerType::STUN:
			AddComponent(new Aura(*this, Enemy::Event::STUN, 800, 7.0, (NearestGOFinder&)stageState, "Enemy"));
			break;
		case TowerType::SHOCK:
            sp.SetFrameCount(8);
            sp.SetFrameTime(0.5);
			AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "Enemy", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/SpriteSheets/bullet_choquelvl1.png", 4, 1));
			break;
	}

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
