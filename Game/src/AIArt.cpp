#include "AIArt.h"

//enum AIState{WALKING,WAITING,STUNNED,STATE_NUM};
//enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,STUN,NOT_STUN,EVENT_NUM}; 

AIArt::AIArt(float speed, int dest, TileMap &tileMap, GameObject &associated, WaveManager &wManager):speed(speed),destTile(dest), pathIndex(0),tileMap(tileMap),associated(associated), waveManager(wManager){
	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	Vec2 originCoord= associated.box.Center();
	path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
	actualTileweight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
	vecSpeed = Vec2(0.0,0.0);
	lastDistance = std::numeric_limits<float>::max();

	dfa[AIState::WALKING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::WALKING][AIEvent::NONE] = AIState::WALKING;

	dfa[AIState::WAITING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WAITING][AIEvent::PATH_FREE] = AIState::WALKING;
	dfa[AIState::WAITING][AIEvent::NONE] = AIState::WAITING;

	dfa[AIState::STUNNED][AIEvent::NOT_STUN] = AIState::WALKING;
	dfa[AIState::STUNNED][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::STUNNED][AIEvent::NONE] = AIState::STUNNED;

	actualState = AIState::WALKING;
	
	tileMap.ObserveMapChanges(this);
}

AIArt::~AIArt(void){
	tileMap.RemoveObserver(this);
	delete heuristic;
}

AIArt::AIEvent AIArt::ComputeEvents(){
	if(actualState == AIState::WALKING){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::WAITING){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(!path->empty()){
			//std::cout << "PATH_FREE" << std::endl;
			return AIEvent::PATH_FREE;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::STUNNED){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::NOT_STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{return NONE;}
	}
	return NONE;
}

void AIArt::Update(float dt){
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
	else if(actualState == AIState::WAITING){
		if(tileMap.GetCoordTilePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0) == destTile){
			associated.RequestDelete();
			waveManager.NotifyEnemyGotToHisDestiny();
		}
	}
	else{
		//Aqui executa animações do efeito estonteante
	}
}

void AIArt::NotifyTileMapChanged(int tilePosition){
	if(path->end() != std::find(path->begin()+pathIndex, path->end(), tilePosition)){
		Vec2 originCoord= associated.box.Center();
		path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
		tempDestination = Vec2(tileMap.GetTileSize().x * ((*path)[pathIndex] % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path)[pathIndex] / tileMap.GetWidth()));
		vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / actualTileweight);
		pathIndex= 0;
		lastDistance = std::numeric_limits<float>::max();
	}
}

bool AIArt::Is(ComponentType type) const{
	return (type == ComponentType::AI_ART);
}
