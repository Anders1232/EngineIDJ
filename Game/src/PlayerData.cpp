#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

#define LIFE_LOST_POINTS -11

PlayerData* PlayerData::instance = nullptr;

PlayerData& PlayerData::GetInstance(void) {
	if (nullptr == PlayerData::instance) {
		PlayerData::instance = new PlayerData();
	}
	return *PlayerData::instance;
}

void PlayerData::Reset(void) {
	if (nullptr != PlayerData::instance) {
		delete PlayerData::instance;
	}
	PlayerData::instance = new PlayerData();
}

PlayerData::PlayerData() {
	points = 0;
	gold = START_MONEY;
	kills = 0;
	lifes = TOTAL_LIFES;
}

PlayerData::~PlayerData() {
}

void PlayerData::Render() const {
}

void PlayerData::Update(float dt) {
}

bool PlayerData::Is(ComponentType type) const{
	return type == PLAYER_DATA;
}

void PlayerData::IncrementKills(void){
	++kills;
	GoldUpdate(-LIFE_LOST_POINTS, true);
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

int PlayerData::GetLifes(void) {
	return lifes;
}

int PlayerData::GetGold(void) {
	return gold;
}

int PlayerData::GetKills(void) {
	return kills;
}

int PlayerData::GetPoints(void) {
	return points;
}
