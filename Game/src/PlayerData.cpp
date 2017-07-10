#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

#define LIFE_LOST_POINTS -11

PlayerData::PlayerData() {
	points = 0;
	gold = START_MONEY;
	kills = 0;
	lifes = TOTAL_LIFES;
}

PlayerData::~PlayerData(){
}

void PlayerData::Render() const {
}

void PlayerData::Update(float dt) {
}

bool PlayerData::Is(ComponentType type) const{
	return type == PLAYER_DATA;
}

void PlayerData::NotifyKillsUpdate(int wave, EnemyData enemyData) {
	++kills;
	PointsUpdate( 1 * (enemyData.gold + (2 * wave)) );
}

void PlayerData::NotifyLifeLost(int wave, EnemyData enemyData) {
	--lifes;
	PointsUpdate( -1 * (enemyData.gold + (2 * wave)) );
}

// decrementa para compra e incrementa pra ganho.
void PlayerData::GoldUpdate(int amount, bool winPoints){
	this->gold += amount;

    if(winPoints) {
        PointsUpdate(gold);
    }
}

// decrementa para perda de vida e incrementa pra kills.
void PlayerData::PointsUpdate(int amount){
	points += amount;
}

void PlayerData::DecrementLife(){
	--lifes;
	PointsUpdate(LIFE_LOST_POINTS);
}

int PlayerData::GetLifes(){
	return lifes;
}

int PlayerData::GetPlayerGold(){
	return gold;
}
