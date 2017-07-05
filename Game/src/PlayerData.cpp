#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

PlayerData::PlayerData(): HUDcanvas(), 
						playerTable(),
						boardName("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board", UIelement::BehaviorType::FIT ,false),
						playerPoints("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Points: 0", UIelement::BehaviorType::FIT ,false),
						playerGold("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Gold: 0", UIelement::BehaviorType::FIT ,false),
						playerKills("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Kills: 0", UIelement::BehaviorType::FIT ,false),
						playerLifes("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255},"Lifes: 30", UIelement::BehaviorType::FIT ,false){

	points = 0;
	gold = 0;
	kills = 0;
	lifes = TOTAL_LIFES;
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	printf("oi\n");
	playerTable.SetAnchors({0.0,0.0},{0.0,0.0} );
	playerTable.SetOffsets( { 0.0, -160.0}, { 240., 200.} );
	printf("oi\n");
	playerTable.groupedElements.emplace_back(&boardName);
	printf("oi\n");
	playerTable.groupedElements.emplace_back(&playerPoints);
	printf("oi\n");
	playerTable.groupedElements.emplace_back(&playerGold);
	printf("oi\n");
	playerTable.groupedElements.emplace_back(&playerKills);
	printf("oi\n");
	playerTable.groupedElements.emplace_back(&playerLifes);

}

PlayerData::~PlayerData(){

}

void PlayerData::Render() const{
	boardName.Render(true);

	playerPoints.Render();
	playerGold.Render();
	playerKills.Render();
	playerLifes.Render();
}
void PlayerData::Update(GameObject &associated, float dt){
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
}

// decrementa para perda de vida e incrementa pra kills.
void PlayerData::PointsUpdate(int amount){
	points += amount;
}

PlayerData& PlayerData::GetInstance(void){
	static PlayerData playerData;
	return playerData;
}


void PlayerData::DecrementLife(){
	lifes--;
}