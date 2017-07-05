#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

PlayerData::PlayerData(): HUDcanvas(), 
						boardName("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board",UIelement::BehaviorType::FIT ,false),
						playerTable(){
	points = 0;
	gold = 0;
	kills = 0;
	lifes = TOTAL_LIFES;
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);

	playerTable.SetAnchors({0.0,0.0},{0.0,0.0} );
	playerTable.SetOffsets( { 0.0, -160.0}, { 240., 200.} );
	playerTable.groupedElements.emplace_back(&boardName);

}

PlayerData::~PlayerData(){

}

void PlayerData::Render() const{
	boardName.Render(true);
}
void PlayerData::Update(GameObject &associated, float dt){
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	
	HUDcanvas.Update(dt, winSize);

	playerTable.Update(dt, HUDcanvas);
	boardName.Update(dt, playerTable);
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