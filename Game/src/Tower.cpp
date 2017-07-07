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
			type == TowerType::ANTIBOMB ? "img/SpriteSheets/anti-bomba.png" :
			type == TowerType::STUN ? "img/tower/torrestun.png" :
			type == TowerType::SHOCK ? "img/SpriteSheets/torrechoque_lvl1.png" :
			"",
			true,
			0.5,
			type == TowerType::SMOKE ? 1:
			type == TowerType::ANTIBOMB ? 8:
			type == TowerType::STUN ? 1:
			type == TowerType::SHOCK ? 8: 1)
			,type(type){
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
			AddComponent(new Shooter(*this, (NearestGOFinder&)stageState, "BOMB", 5000, 2.0, Shooter::TargetPolicy::ALWAYS_NEAREST, true, 500, 5000, "img/SpriteSheets/anti-bomba_ativ_spritesheet.png", 11, 1));
			break;
		case TowerType::STUN:
			AddComponent(new Aura(*this, Enemy::Event::STUN, 800, 7.0, (NearestGOFinder&)stageState, "Enemy"));
			break;
		case TowerType::SHOCK:
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

	switch(type){
		case TowerType::SMOKE:
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
			break;
		case TowerType::ANTIBOMB:
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
			break;
		case TowerType::STUN:
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
			break;
		case TowerType::SHOCK:
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
			break;
		default:
			Game::GetInstance().GetCurrentState().AddObject(new Animation(box.x,box.y,rotation,"img/SpriteSheets/explosao_spritesheet.png",9,0.1,true));
			break;

	}
	
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
