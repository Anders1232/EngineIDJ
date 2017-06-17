#include "Enemy.h"


#include "Camera.h"
#include "Error.h"
#include "AIGoDown.h"
#include "HitPoints.h"

#define ENEMY_MOVE_SPEED (120.)

Enemy::Enemy(Vec2 position, int life)
		: sp("img/enemy/teste-cor.png", true, 0.0, 1), dead(false) {
	box = position;
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
	
	sp.SetScale(0.8);
	sp.SetFrame(1);
}

Enemy::Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint): sp(), dead(false){
	box = position;
	this->enemyIndex = enemyIndex; 
	this->quant = quant; 
	this->baseHP = baseHP; 
	this->endPoint = endPoint;

	spName.Open(enemyData.spName);
	//bodySpName.Open(enemyData.bodySpName);
	//headSpName.Open(enemyData.headSpName);
	//pantsSpName.Open(enemyData.pantsSpName);
	
	spName.SetScaleX(enemyData.scaleX);
	spName.SetScaleY(enemyData.scaleY);
	//bodySpName.SetScaleX(enemyData.scaleX);
	//headSpName.SetScaleX(enemyData.scaleX);
	//pantsSpName.SetScaleX(enemyData.scaleX);
	//bodySpName.SetScaleY(enemyData.scaleY);
	//headSpName.SetScaleY(enemyData.scaleY);
	//pantsSpName.SetScaleY(enemyData.scaleY);

	spName.SetFrame(1);
	//bodySpName.SetFrame(1);
	//headSpName.SetFrame(1);
	//pantsSpName.SetFrame(1);
	
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED)); //arg endPoint
	//components.emplace_back(new PathFinding(endPoint)); //arg endPoint
	components.push_back(new HitPoints(baseHP)); 
}


Enemy::~Enemy(){
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
