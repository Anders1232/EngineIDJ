#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"


PlayerData::PlayerData():name("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board",UIelement::BehaviorType::FIT ,false){
	points = 0;
	gold = 0;
	kills = 0;
	lifes = TOTAL_LIFES;
	//name.box.x=0;
	//name.box.y=0;
}
PlayerData::~PlayerData(){

}

void PlayerData::Render() const{
	name.Render();
}
void PlayerData::Update(GameObject &associated, float dt){

}

bool PlayerData::Is(ComponentType type) const{
	return type == PLAYER_DATA;
}

void PlayerData::NotifyKillsUpdate(int wave, EnemyData enemyData){
	++kills;
	PointsUpdate(enemyData.gold + (2 * wave) );
}

void PlayerData::NotifyLifeLost(int wave, EnemyData enemyData){
	--lifes;
	PointsUpdate( -1 * (enemyData.gold + (2 * wave)) );
}

// decrementa para compra e incrementa pra ganho.
void PlayerData::GoldUpdate(int amount){
	this->gold += amount; 
}

// decrementa para perda de vida e incrementa pra kills.
void PlayerData::PointsUpdate(int amount){
	points += amount;
}