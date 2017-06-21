#include "Enemy.h"

#include "Camera.h"
#include "Error.h"

Enemy::Enemy(Vec2 position,EnemyType type, int life):type(type), sp("img/enemy/teste-cor.png", true, 0.0, 1), life(life) {
	box = position;
	dead = false;
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
		components[i]->Update(dt);
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

EnemyType Enemy::GetType(void) const{

	return type;

}
