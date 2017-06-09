#include "Enemy.h"

#include "AIGoDown.h"
#include "Camera.h"
#include "Error.h"

#define ENEMY_MOVE_SPEED (120.)

<<<<<<< HEAD
Enemy::Enemy(Vec2 position, int life ):sp("img/enemy/reference_assembled.png", true,0.0,4), dead(false){
	box= position;
=======
Enemy::Enemy(Vec2 position, int life)
		: sp("img/enemy/teste-cor.png", 0.0, 1), dead(false) {
	box = position;
>>>>>>> c5107e99d962ecdbc0c16f62d763d212369ef492
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
	
	sp.SetScale(0.8);
	sp.SetFrame(1);
}

Enemy::~Enemy() {
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
}

void Enemy::Update(float dt) {
	int forLimit = components.size();
	for(int i = 0; i < forLimit; i++){
		components[i]->Update(*this, dt);
	}
}

void Enemy::Render(void) {
	sp.Render(box);
}

bool Enemy::IsDead(void) {
	return false;
}

void Enemy::RequestDelete() {}

void Enemy::NotifyCollision(GameObject &object) {}

bool Enemy::Is(string type) {
	return type == "Enemy";
}

Rect Enemy::GetWorldRenderedRect(void) const {
	return Camera::WorldToScreen(box);
}
