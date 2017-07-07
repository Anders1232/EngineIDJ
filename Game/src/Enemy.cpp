#include "Enemy.h"
#include "AIEngineer.h"
#include "AIMedic.h"
#include "AIArt.h"
#include "AIQuimic.h"
#include "AIGoTo.h"
#include "Camera.h"
#include "Error.h"
#include "AIGoDown.h"
#include "HitPoints.h"
#include "Timer.h"

Enemy::Enemy(Vec2 position, int enemyIndex, EnemyData enemyData, uint baseHP, uint endPoint, TileMap & tileMap, WaveManager &wManager)
	: sp(EnemyDirections::ENEMY_DIRECTIONS_SIZE), dead(false), direction(EnemyDirections::DOWN), walkingSound("audio/Ambiente/andando2.wav"){
	box = position;
	this->enemyIndex = enemyIndex; 
	this->baseHP = baseHP; 
	this->endPoint = endPoint;
	eventTimer = Timer();

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
			REPORT_DEBUG("Enemy type: HOSTILE "<< enemyData.enemyType);
			type = EnemyType::HOSTILE;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 85;
					sp[i][i2].colorMultiplier.g = 85;
					sp[i][i2].colorMultiplier.b = 85;
				}
			}
			components.emplace_back(new AIGoTo(ENEMY_ENGINEER_MOVE_SPEED, endPoint, tileMap , *this));
			break;
		case EnemyType::NEUTRAL:
			REPORT_DEBUG("Enemy type: NEUTRAL "<< enemyData.enemyType);
			type = EnemyType::NEUTRAL;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 255;
					sp[i][i2].colorMultiplier.g = 255;
					sp[i][i2].colorMultiplier.b = 255;
				}
			}
			components.emplace_back(new AIGoTo(ENEMY_ENGINEER_MOVE_SPEED, endPoint, tileMap , *this));
			break;
		case EnemyType::ENGINEER:
			REPORT_DEBUG("Enemy type: ENGINEER "<< enemyData.enemyType);
			type = EnemyType::ENGINEER;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 44;
					sp[i][i2].colorMultiplier.g = 44;
					sp[i][i2].colorMultiplier.b = 105;
				}
			}
			components.emplace_back(new AIEngineer(ENEMY_ENGINEER_MOVE_SPEED, endPoint, tileMap , *this, wManager));
			break;
		case EnemyType::ARQUITET:
			REPORT_DEBUG("Enemy type: ARQUITET "<< enemyData.enemyType);
			type = EnemyType::ARQUITET;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 255;
					sp[i][i2].colorMultiplier.g = 51;
					sp[i][i2].colorMultiplier.b = 255;
				}
			}
			components.emplace_back(new AIEngineer(ENEMY_ENGINEER_MOVE_SPEED, endPoint, tileMap , *this, wManager));
			break;
		case EnemyType::ART:
			REPORT_DEBUG("Enemy type: ART "<< enemyData.enemyType);
			type = EnemyType::ART;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 220;
					sp[i][i2].colorMultiplier.g = 90;
					sp[i][i2].colorMultiplier.b = 15;
				}
			}
			components.emplace_back(new AIArt(ENEMY_ART_MOVE_SPEED, endPoint, tileMap, *this, wManager));
			//components.emplace_back(new AIGoDown(500, endPoint, tileMap, *this, wManager));
			
			break;
		case EnemyType::QUIMIC:
			REPORT_DEBUG("Enemy type: QUIMIC "<< enemyData.enemyType);
			type = EnemyType::QUIMIC;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 100;
					sp[i][i2].colorMultiplier.g = 250;
					sp[i][i2].colorMultiplier.b = 100;
				}
			}
			components.emplace_back(new AIQuimic(ENEMY_QUIMIC_MOVE_SPEED, endPoint, tileMap, *this, wManager));
			break;
		case EnemyType::MEDIC:
			REPORT_DEBUG("Enemy type: MEDIC "<< enemyData.enemyType);
			type = EnemyType::MEDIC;
			for(uint i =0; i < EnemyDirections::ENEMY_DIRECTIONS_SIZE; i++){
				for(uint i2= 0; i2 < sp[i].size(); i2++){
					sp[i][i2].colorMultiplier.r = 190;
					sp[i][i2].colorMultiplier.g = 250;
					sp[i][i2].colorMultiplier.b = 10;
				}
			}
			components.emplace_back(new AIMedic(ENEMY_QUIMIC_MOVE_SPEED, endPoint, tileMap, *this, wManager));
			break;
		default:
			Error("Unkown Enemy type: "<< enemyData.enemyType << END_LINE);
			break;
	}
	hitpoints = new HitPoints(baseHP,*this, enemyData.scaleX);
	components.push_back(hitpoints);

	walkingSound.Play(-1);

	box.w= sp[EnemyDirections::DOWN][3].GetWidth();
	box.h= sp[EnemyDirections::DOWN][3].GetHeight();
}

Enemy::~Enemy(){
	REPORT_I_WAS_HERE;
	walkingSound.Stop();
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
	sp.clear();
}

void Enemy::Update(float dt) {
	int forLimit = components.size();
	Vec2 positionBefore= box;
	for(int i = 0; i < forLimit; i++){
		components[i]->Update(dt);
	}
	UpdateEnemyDirection(positionBefore);
	if(hitpoints->GetHp() < 0){
		dead = true;
	}
	if(eventTimer.Get() > MAX_EVENT_TIME){
		lastEvent = Event::NONE;
	}
	eventTimer.Update(dt);
}

void Enemy::Render(void) {
	REPORT_DEBUG("\t Box:: x("<<box.x<<"), y(" <<box.y<< "), w("<<box.w<<"), h("<<box.h<<")");
	for(uint i=0; i< sp[direction].size(); i++){
		sp[direction][i].Render(box);
	}
	for(uint i=0; i< components.size(); i++){
		components[i]->Render();
	}
	hitpoints->Render();
}

bool Enemy::IsDead(void) {
	return dead;
}

void Enemy::RequestDelete(void) {
	dead = true;
}

void Enemy::NotifyCollision(GameObject &object) {
	if(object.Is("Bullet")){
		if(((Bullet&)object).getTargetType() == "Enemy"){
			hitpoints->Damage(ENEMY_BULLET_DAMAGE);
		}
	}
}

void Enemy::NotifyEvent(Event e){

	lastEvent = e;
	eventTimer.Restart();

}

Enemy::Event Enemy::GetLastEvent(){

	return(lastEvent);
	
}

bool Enemy::Is(string type) {
	return type == "Enemy";
}

Rect Enemy::GetWorldRenderedRect(void) const {
	return Camera::WorldToScreen(box);
}

EnemyType Enemy::GetType(void) const{
	return type;
}

void Enemy::UpdateEnemyDirection(Vec2 lastPosition){
	int inclination= ( (int)( (lastPosition-(Vec2)box).Inclination()*CONVERSAO_GRAUS_RADIANOS) )%360;
	if(0 > inclination){
		inclination+=360;
	}
	REPORT_DEBUG("\t inclinação= "<<inclination);
	if(45 <= inclination && 135 > inclination){
		direction= EnemyDirections::UP;
	}
	if(135 <= inclination && 225 > inclination){
		direction= EnemyDirections::RIGHT;
	}
	if(225 <= inclination && 315 > inclination){
		direction= EnemyDirections::DOWN;
	}
	else{
		direction= EnemyDirections::LEFT;
	}
}

