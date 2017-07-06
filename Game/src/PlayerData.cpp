#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

#define LIFE_LOST -11

PlayerData::PlayerData(): HUDcanvas(), 
						playerTable(),
						boardName("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board", UIelement::BehaviorType::FIT ,false),
						playerPoints("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Points: 0", UIelement::BehaviorType::FIT ,false),
						playerGold("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Gold: 0", UIelement::BehaviorType::FIT ,false),
						playerKills("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Kills: 0", UIelement::BehaviorType::FIT ,false),
						playerLifes("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255},"Lifes: 30", UIelement::BehaviorType::FIT ,false){

	points = 0;
	gold = 0;
	kills = 0;
	lifes = TOTAL_LIFES;
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	playerTable.SetAnchors({0.01,0.01},{0.01,0.01} );
	playerTable.SetOffsets( { 0.0, 0.0}, { 220., 140.} );
	playerTable.groupedElements.emplace_back(&boardName);
	playerTable.groupedElements.emplace_back(&playerPoints);
	playerTable.groupedElements.emplace_back(&playerGold);
	playerTable.groupedElements.emplace_back(&playerKills);
	playerTable.groupedElements.emplace_back(&playerLifes);


}

PlayerData::~PlayerData(){

}

void PlayerData::Render() const{
	playerTable.Render();

	boardName.Render();

	playerPoints.Render();
	playerGold.Render();
	playerKills.Render();
	playerLifes.Render();
}
void PlayerData::Update(float dt){
	Rect winSize(0.0, 0.0, Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	
	HUDcanvas.Update(dt, winSize);
	playerTable.Update(dt, HUDcanvas);

	boardName.Update(dt, playerTable);
	playerPoints.Update(dt, playerTable);
	playerGold.Update(dt, playerTable);
	playerKills.Update(dt, playerTable);
	playerLifes.Update(dt, playerTable);

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
	playerGold.SetText("Gold: " + std::to_string(gold));
	PointsUpdate(gold);
}

// decrementa para perda de vida e incrementa pra kills.
void PlayerData::PointsUpdate(int amount){
	points += amount;
	playerPoints.SetText("Points: " + std::to_string(points));
}

PlayerData& PlayerData::GetInstance(void){
	static PlayerData playerData;
	return playerData;
}


void PlayerData::DecrementLife(){
	--lifes;
	playerLifes.SetText("Lifes: " + std::to_string(lifes));
	PointsUpdate(LIFE_LOST);
}

int PlayerData::GetLifes(){
	return lifes;
}