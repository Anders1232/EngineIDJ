#include "PlayerData.h"
#include "WaveData.h"
#include "Error.h"
#include "Game.h"

#define LIFE_LOST_POINTS -11

PlayerData::PlayerData(): HUDcanvas(), 
						playerTable(),
						goldInfo(),
						coin("img/UI/HUD/moeda_HUD.png"),
						boardName("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board", UIelement::BehaviorType::FIT ,false),
						playerPoints("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Points: 0", UIelement::BehaviorType::FIT ,false),
						playerGold("font/SHPinscher-Regular.otf", 85, UItext::TextStyle::BLENDED, {255,255,255,255}, "150", UIelement::BehaviorType::FIT ,false),
						playerKills("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255}, "Kills: 0", UIelement::BehaviorType::FIT ,false),
						playerLifes("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255},"Lifes: 30", UIelement::BehaviorType::FIT ,false),
						playerWave("font/SHPinscher-Regular.otf", 45, UItext::TextStyle::BLENDED, {255,255,255,255},"Wave: 1", UIelement::BehaviorType::FIT ,false){

	points = 0;
	gold = START_MONEY;
	kills = 0;
	lifes = TOTAL_LIFES;
	//coin.SetSpriteScale(0.2);
    Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	playerTable.SetAnchors({0.01,0.01},{0.01,0.01} );
	playerTable.SetOffsets( { 80.0, 80.0}, { 280., 240.} );
    playerTable.groupedElements.emplace_back(&playerGold);
    playerTable.groupedElements.emplace_back(&playerKills);
	playerTable.groupedElements.emplace_back(&boardName);
	playerTable.groupedElements.emplace_back(&playerPoints);
	playerTable.groupedElements.emplace_back(&playerLifes);
	playerTable.groupedElements.emplace_back(&playerWave);

    goldInfo.SetAnchors({0.01,0.01},{0.01,0.01} );
    goldInfo.SetOffsets( { 30.0, 100.0}, { 120., 140.} );
    goldInfo.groupedElements.emplace_back(&coin);
    goldInfo.groupedElements.emplace_back(&playerGold);

}

PlayerData::~PlayerData(){
}

void PlayerData::Render() const{
	// playerTable.Render();
    // goldInfo.Render();
	//boardName.Render();

	//playerPoints.Render();
    // coin.Render();
	// playerGold.Render();
	// playerKills.Render();
	//playerLifes.Render();
	//playerWave.Render();
}
void PlayerData::Update(float dt){
	// Rect winSize(0.0, 0.0, Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	
	// HUDcanvas.Update(dt, winSize);
	// playerTable.Update(dt, HUDcanvas);
    // goldInfo.Update(dt, HUDcanvas);

    //boardName.Update(dt, playerTable);
    // coin.Update(dt, goldInfo);
    // playerGold.Update(dt, goldInfo);

	// playerPoints.Update(dt, playerTable);

    // playerKills.Update(dt, playerTable);
	// playerLifes.Update(dt, playerTable);
	// playerWave.Update(dt, playerTable);


}

bool PlayerData::Is(ComponentType type) const{
	return type == PLAYER_DATA;
}

void PlayerData::NotifyKillsUpdate(int gold){
	++kills;
    playerKills.SetText("Kills: " + std::to_string(kills));
}

void PlayerData::NotifyLifeLost(int wave, EnemyData enemyData){
	--lifes;
	PointsUpdate( -1 * (enemyData.gold + (2 * wave)) );
}

// decrementa para compra e incrementa pra ganho.
void PlayerData::GoldUpdate(int amount, bool winPoints){
	this->gold += amount; 
	playerGold.SetText(std::to_string(gold));

    if(winPoints) {
        PointsUpdate(gold);
    }
}

// decrementa para perda de vida e incrementa pra kills.
void PlayerData::PointsUpdate(int amount){
	points += amount;
    playerPoints.SetText("Points: " + std::to_string(points));

}



void PlayerData::DecrementLife(){
	--lifes;
	playerLifes.SetText("Lifes: " + std::to_string(lifes));
	PointsUpdate(LIFE_LOST_POINTS);
}

int PlayerData::GetLifes(){
	return lifes;
}

void PlayerData::CountNextWave(int wave){
	playerWave.SetText("Wave: " + std::to_string(wave) );
}

int PlayerData::GetPlayerGold(){
	return gold;
}
