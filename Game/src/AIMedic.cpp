#include <algorithm>
#include "AIMedic.h"

AIMedic::AIMedic(float speed,int dest,TileMap& tilemap,GameObject &associated,WaveManager &wManager):speed(speed),destTile(dest), pathIndex(0),tileMap(tilemap),associated(associated),waveManager(wManager){
	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	Vec2 originCoord= associated.box.Center();
	path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tilemap.GetCoordTilePos(originCoord, false, 0), dest, "map/WeightData.txt");
	actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
	vecSpeed = Vec2(0.0,0.0);
	lastDistance = std::numeric_limits<float>::max();
	randomMaxTimer = 0;

	dfa[AIState::WALKING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::WALKING][AIEvent::SMOKE] = AIState::WALKING_SLOWLY;
	dfa[AIState::WALKING][AIEvent::NONE] = AIState::WALKING;

	dfa[AIState::WAITING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WAITING][AIEvent::PATH_FREE] = AIState::WALKING;
	dfa[AIState::WAITING][AIEvent::NONE] = AIState::WAITING;

	dfa[AIState::STUNNED][AIEvent::NOT_STUN] = AIState::WALKING;
	dfa[AIState::STUNNED][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::STUNNED][AIEvent::NONE] = AIState::STUNNED;

	dfa[AIState::WALKING_SLOWLY][AIEvent::NOT_SMOKE] = AIState::WALKING;
	dfa[AIState::WALKING_SLOWLY][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::WALKING_SLOWLY][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING_SLOWLY][AIEvent::NONE] = AIState::WALKING_SLOWLY;

	actualState = AIState::WALKING;
	
	tileMap.ObserveMapChanges(this);
}

AIMedic::~AIMedic(void){
	tileMap.RemoveObserver(this);
	delete heuristic;
}

AIMedic::AIEvent AIMedic::ComputeEvents(){
	if(actualState == AIState::WALKING){
		if(((Enemy&)associated).GetLastEvent() == Enemy::Event::STUN){
			return AIEvent::STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else if(((Enemy&)associated).GetLastEvent() == Enemy::Event::SMOKE){
			return AIEvent::SMOKE;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::WALKING_SLOWLY){
		if(((Enemy&)associated).GetLastEvent() == Enemy::Event::STUN){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(((Enemy&)associated).GetLastEvent() != Enemy::Event::SMOKE){// Aqui verifica-se o fim da colisão com o elemento de fumaça
			return AIEvent::NOT_SMOKE;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::WAITING){
		if(((Enemy&)associated).GetLastEvent() == Enemy::Event::STUN){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(!path->empty()){
			//std::cout << "PATH_FREE" << std::endl;
			return AIEvent::PATH_FREE;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::STUNNED){
		if(((Enemy&)associated).GetLastEvent() != Enemy::Event::STUN){// Aqui verifica-se o fim da colisão com o elemento estonteante
			return AIEvent::NOT_STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{
			return NONE;
		}
	}
	return NONE;
}

void AIMedic::Update(float dt){
	//enum AIState{WALKING,WALKING_SLOWLY,WAITING,STUNNED,STATE_NUM};
	//enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,SMOKE,NOT_SMOKE,STUN,NOT_STUN,EVENT_NUM}; 

	AIEvent actualTransition = ComputeEvents();
	actualState = dfa[actualState][actualTransition];
	if(actualState == AIState::WALKING){
		if(pathIndex != path->size()){
			tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
			float distance = associated.box.Center().VecDistance(tempDestination).Magnitude();
			if((vecSpeed.MemberMult(dt)).Magnitude() >= distance || lastDistance < distance){
				Vec2 movement= tempDestination-Vec2(associated.box.w/2, associated.box.h/2);
				associated.box.x = movement.x;
				associated.box.y = movement.y;
				pathIndex++;
				if(pathIndex != path->size()){
					tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
					lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
					actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
				}
			}
			else if(vecSpeed.Magnitude() == 0.0){
				actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
			}
			else{
				associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
				associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);
				lastDistance = distance;
			}
		}
	}
	else if(actualState == AIState::WALKING_SLOWLY){
		if(pathIndex != path->size()){
			tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
			float distance = associated.box.Center().VecDistance(tempDestination).Magnitude();
			if((vecSpeed.MemberMult(dt)).Magnitude() >= distance || lastDistance < distance){
				Vec2 movement= tempDestination-Vec2(associated.box.w/2, associated.box.h/2);
				associated.box.x = movement.x;
				associated.box.y = movement.y;
				pathIndex++;
				if(pathIndex != path->size()){
					tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
					lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
					actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER)) * 3;
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed /actualTileweight);
				}
			}
			else if(vecSpeed.Magnitude() == 0.0){
				actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER)) * 3;
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
			}
			else{
				associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
				associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);
				lastDistance = distance;
			}
		}
	}
	else if(actualState == AIState::WAITING){
		if(tileMap.GetCoordTilePos(associated.box.Center(), false, 0) == destTile){
			associated.RequestDelete();
			waveManager.NotifyEnemyGotToHisDestiny();
		}
		else{
			if(getPathTimer.Get() > randomMaxTimer){
				getPathTimer.Restart();
				randomMaxTimer = rand()%3;
				Vec2 originCoord= associated.box.Center();
				path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
				TEMP_REPORT_I_WAS_HERE;
				if(path->size() > 0){
					TEMP_REPORT_I_WAS_HERE;
					pathIndex = 0;
					tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
					lastDistance = std::numeric_limits<float>::max();
				}

			}
			getPathTimer.Update(dt);
		}
	}
	else if(actualState == AIState::STUNNED){
		//Aqui executa animações do efeito estonteante
	}
}

void AIMedic::NotifyTileMapChanged(int tilePosition){
	if(path->end() != std::find(path->begin()+pathIndex, path->end(), tilePosition)){
		Vec2 originCoord= associated.box.Center();
		path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
		if(path->size() > 0){
			pathIndex = 0;
			tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
			vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
			lastDistance = std::numeric_limits<float>::max();
		}
	}
}

bool AIMedic::Is(ComponentType type) const{
	return (type == ComponentType::AI_MEDIC);
}
