#include "Enemy.h"

#include "Camera.h"
#include "Error.h"
#include "AIGoDown.h"
#include "HitPoints.h"
/*
Enemy::Enemy(Vec2 position, int life)
		: sp("img/enemy/teste-cor.png", true, 0.0, 1), dead(false) {
	box = position;
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
	
	sp.SetScale(0.8);
	sp.SetFrame(1);

}
*/
Enemy::Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint)
	: sp(EnemyDirections::ENEMY_DIRECTIONS_SIZE), dead(false), direction(EnemyDirections::DOWN){
	box = position;
	this->enemyIndex = enemyIndex; 
	this->baseHP = baseHP; 
	this->endPoint = endPoint;

	for(uint i=0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
		sp[i]= vector<Sprite>();
	}

	std::string basePath= "img/"+enemyData.spFolder;
	basePath= basePath+ "/";

	sp[EnemyDirections::UP].emplace_back(basePath+"perna_tras.png", true, 0., 1);
	sp[EnemyDirections::UP].emplace_back(basePath+"cabeca_tras.png", true, 0., 1);
	sp[EnemyDirections::UP].emplace_back(basePath+"cabelo_tras.png", true, 0., 1);
	sp[EnemyDirections::UP].emplace_back(basePath+"torso_tras.png", true, 0., 1);
	
	box = position;
	sp[EnemyDirections::RIGHT].emplace_back(basePath+"perna_dir.png", true, 0., 1);
	sp[EnemyDirections::RIGHT].emplace_back(basePath+"cabeca_dir.png", true, 0., 1);
	sp[EnemyDirections::RIGHT].emplace_back(basePath+"cabelo_dir.png", true, 0., 1);
	sp[EnemyDirections::RIGHT].emplace_back(basePath+"torso_dir.png", true, 0., 1);

	sp[EnemyDirections::DOWN].emplace_back(basePath+"perna_frente.png", true, 0., 1);
	sp[EnemyDirections::DOWN].emplace_back(basePath+"cabeca_frente.png", true, 0., 1);
	sp[EnemyDirections::DOWN].emplace_back(basePath+"cabelo_frente.png", true, 0., 1);
	sp[EnemyDirections::DOWN].emplace_back(basePath+"torso_frente.png", true, 0., 1);
	
	sp[EnemyDirections::LEFT].emplace_back(basePath+"perna_esq.png", true, 0., 1);
	sp[EnemyDirections::LEFT].emplace_back(basePath+"cabeca_esq.png", true, 0., 1);
	sp[EnemyDirections::LEFT].emplace_back(basePath+"cabelo_esq.png", true, 0., 1);
	sp[EnemyDirections::LEFT].emplace_back(basePath+"torso_esq.png", true, 0., 1);
	
	for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
		for(uint i2= 0; i2 < sp[i].size(); i2++){
			sp[i][i2].SetScaleX(enemyData.scaleX);
			sp[i][i2].SetScaleY(enemyData.scaleY);
		}
	}
	
	for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
		for(uint i2= 0; i2 < sp[i].size(); i2++){
			sp[i][i2].SetFrame(1);
		}
	}

	//each type will have their own components. dando invalid read.
	switch(enemyData.enemyType){
		case EnemyType::HOSTILE:
			std::cout << "Enemy type: HOSTILE "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 85;
					sp[i][i2].colorMultiplier.g = 85;
					sp[i][i2].colorMultiplier.b = 85;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_HOSTILE_MOVE_SPEED));
			break;
		case EnemyType::NEUTRAL:
			std::cout << "Enemy type: NEUTRAL "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 255;
					sp[i][i2].colorMultiplier.g = 255;
					sp[i][i2].colorMultiplier.b = 255;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
			break;
		case EnemyType::ENGINEER:
			std::cout << "Enemy type: ENGINEER "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 44;
					sp[i][i2].colorMultiplier.g = 44;
					sp[i][i2].colorMultiplier.b = 105;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_ENGINEER_MOVE_SPEED));
			break;
		case EnemyType::ARQUITET:
			std::cout << "Enemy type: ARQUITET "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 255;
					sp[i][i2].colorMultiplier.g = 51;
					sp[i][i2].colorMultiplier.b = 255;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_ARQUITET_MOVE_SPEED));
			break;
		case EnemyType::ART:
			std::cout << "Enemy type: ART "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 220;
					sp[i][i2].colorMultiplier.g = 90;
					sp[i][i2].colorMultiplier.b = 15;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_ART_MOVE_SPEED));
			break;
		case EnemyType::QUIMIC:
			std::cout << "Enemy type: QUIMIC "<< enemyData.enemyType << "\n";
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 100;
					sp[i][i2].colorMultiplier.g = 250;
					sp[i][i2].colorMultiplier.b = 100;
				}
			}
			components.emplace_back(new AIGoDown(ENEMY_QUIMIC_MOVE_SPEED));
			break;
		default:
			std::cout << "Unkown Enemy type: "<< enemyData.enemyType << "\n";
			break;
	}
	hitpoints = new HitPoints(baseHP);
	components.push_back(hitpoints);
}


Enemy::~Enemy(){
	REPORT_I_WAS_HERE;
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
	sp.clear();
}

void Enemy::Update(float dt) {
	int forLimit = components.size();
	for(int i = 0; i < forLimit; i++){
		components[i]->Update(*this, dt);
	}
	if(hitpoints->GetHp() < 0){
		dead = true;
	}
}

void Enemy::Render(void) {
	REPORT_DEBUG("\t Box:: x("<<box.x<<"), y(" <<box.y<< "), w("<<box.w<<"), h("<<box.h<<")");
	for(uint i=0; i< sp[direction].size(); i++){
		sp[direction][i].Render(box);
	}
	for(uint i= 0; i < sp[direction].size(); i++){
		sp[direction][i].Render(box);
	}
	hitpoints->Render(*this);
}

bool Enemy::IsDead(void) {
	return dead;
}

void Enemy::RequestDelete(void) {}

void Enemy::NotifyCollision(GameObject &object) {
/*
	if (other.Is("Bullet")){
		if( ( (Bullet&)other).GetTargetsPlayer()==false){
			hp->Damage(DMG); 
		}
	}
*/	
}

bool Enemy::Is(string type) {
	return type == "Enemy";
}

Rect Enemy::GetWorldRenderedRect(void) const {
	return Camera::WorldToScreen(box);
}

void Enemy::NotifyDeath(){
	dead = true;
}
