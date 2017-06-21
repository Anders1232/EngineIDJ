#include "Enemy.h"

#include "Camera.h"
#include "Error.h"
#include "AIGoDown.h"
#include "HitPoints.h"

Enemy::Enemy(Vec2 position, int life)
		: sp("img/enemy/teste-cor.png", true, 0.0, 1), dead(false) {
	box = position;
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED));
	
	sp.SetScale(0.8);
	sp.SetFrame(1); 

}

Enemy::Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint)
: sp(enemyData.spName, true, 0.0, 1), dead(false){
	box = position;
	this->enemyIndex = enemyIndex; 
	this->baseHP = baseHP; 
	this->endPoint = endPoint;

	//spName.Open(enemyData.spName);
	//bodySpName.Open(enemyData.bodySpName);
	//headSpName.Open(enemyData.headSpName);
	//pantsSpName.Open(enemyData.pantsSpName);

	sp.SetScaleX(enemyData.scaleX);
	sp.SetScaleY(enemyData.scaleY);
	//bodySpName.SetScaleX(enemyData.scaleX);
	//headSpName.SetScaleX(enemyData.scaleX);
	//pantsSpName.SetScaleX(enemyData.scaleX);
	//bodySpName.SetScaleY(enemyData.scaleY);
	//headSpName.SetScaleY(enemyData.scaleY);
	//pantsSpName.SetScaleY(enemyData.scaleY);

	sp.SetFrame(1);
	//bodySpName.SetFrame(1);
	//headSpName.SetFrame(1);
	//pantsSpName.SetFrame(1);

	//each type will have their own components. dando invalid read.
	switch(enemyData.enemyType){
		case EnemyType::HOSTILE:
			std::cout << "Enemy type: HOSTILE "<< enemyData.enemyType << "\n";
			break;
		case EnemyType::NEUTRAL:
			std::cout << "Enemy type: NEUTRAL "<< enemyData.enemyType << "\n";
			break;
		case EnemyType::ENGINEER:
			std::cout << "Enemy type: ENGINEER "<< enemyData.enemyType << "\n";
			break;
		case EnemyType::ARQUITET:
			std::cout << "Enemy type: ARQUITET "<< enemyData.enemyType << "\n";
			break;
		case EnemyType::ART:
			std::cout << "Enemy type: ART "<< enemyData.enemyType << "\n";
			break;
		case EnemyType::QUIMIC:
			std::cout << "Enemy type: QUIMIC "<< enemyData.enemyType << "\n";
			break;
		default:
			std::cout << "Unkown Enemy type: "<< enemyData.enemyType << "\n";
			break;
	}
	components.emplace_back(new AIGoDown(ENEMY_MOVE_SPEED)); //arg endPoint
	//components.emplace_back(new PathFinding(endPoint)); //arg endPoint
	hp = new HitPoints(baseHP);

	components.push_back(hp);

	//*hp = GetComponent(COMPONENT_Type::IT_POINTS);
	//hp->Damage(); 
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
	REPORT_DEBUG("\t Box:: x("<<box.x<<"), y(" <<box.y<< "), w("<<box.w<<"), h("<<box.h<<")");
	sp.Render(box);
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
