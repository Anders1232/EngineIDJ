#include "AIShooterTower.h"

AIShooterTower::AIShooterTower(GameObject& associated,TileMap& tileMap,std::string bullet): bulletsCoolDown(), tileMap(tileMap), associated(associated), bulletSp(bullet){
}

void AIShooterTower::Update(float dt){
	bulletsCoolDown.Update(dt);
	if(bulletsCoolDown.Get() > TOWER_MAX_BULLET_COOLDOWN){
		bulletsCoolDown.Restart();
		GameObject* target = tileMap.FindNearestGO(associated.box.Center(),std::string("Enemy"));
		if(target != nullptr){
			Vec2 distance = associated.box.Center().VecDistance(target->box.Center());
			float angle = std::atan2(distance.y,distance.x);
			Bullet* bullet = new Bullet(associated.box.Center().x,associated.box.Center().y,angle,BULLET_VEL,BULLET_REACH,bulletSp,std::string("Enemy"),3,0.1);
			Game::GetInstance().GetCurrentState().AddObject(bullet);
		}
	}
}

bool AIShooterTower::Is(std::string type) const{
	return type == "Tower";
}
