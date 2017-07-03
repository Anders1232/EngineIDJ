#include "PlayerData.h"

PlayerData::PlayerData():name("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Player Board",UIelement::BehaviorType::FIT ,false){
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

void PlayerData::NotifyGoldUpdate(int amount){
	this->gold += amount;
}
void PlayerData::NotifyKillsUpdate(){
	++kills;
}
void PlayerData::NotifyLifesUpdate(){
	--lifes;
}