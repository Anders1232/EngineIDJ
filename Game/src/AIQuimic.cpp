#include <algorithm>
#include "AIQuimic.h"

AIQuimic::AIQuimic(float speed, int dest, TileMap &tileMap, GameObject &associated,WaveManager& wManager):speed(speed),destTile(dest), pathIndex(0),tileMap(tileMap),associated(associated),waveManager(wManager){
	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	Vec2 originCoord= associated.box.Center();
	path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
	vecSpeed = Vec2(0.0,0.0);
	lastDistance = std::numeric_limits<float>::max();
	bulletsCoolDown = Timer();

	dfa[AIState::WALKING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING][AIEvent::PATH_BLOCKED] = AIState::SENDING_BOMB;
	dfa[AIState::WALKING][AIEvent::SMOKE] = AIState::WALKING_SLOWLY;
	dfa[AIState::WALKING][AIEvent::NONE] = AIState::WALKING;

	dfa[AIState::SENDING_BOMB][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::SENDING_BOMB][AIEvent::PATH_FREE] = AIState::WALKING;
	dfa[AIState::SENDING_BOMB][AIEvent::NONE] = AIState::SENDING_BOMB;

	dfa[AIState::STUNNED][AIEvent::NOT_STUN] = AIState::WALKING;
	dfa[AIState::STUNNED][AIEvent::PATH_BLOCKED] = AIState::SENDING_BOMB;
	dfa[AIState::STUNNED][AIEvent::NONE] = AIState::STUNNED;

	dfa[AIState::WALKING_SLOWLY][AIEvent::NOT_SMOKE] = AIState::WALKING;
	dfa[AIState::WALKING_SLOWLY][AIEvent::PATH_BLOCKED] = AIState::SENDING_BOMB;
	dfa[AIState::WALKING_SLOWLY][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING_SLOWLY][AIEvent::NONE] = AIState::WALKING_SLOWLY;

	actualState = AIState::WALKING;
	
	tileMap.ObserveMapChanges(this);
}

AIQuimic::~AIQuimic(void){
	tileMap.RemoveObserver(this);
}

AIQuimic::AIEvent AIQuimic::ComputeEvents(){
	if(actualState == AIState::WALKING){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else if(false){// Aqui verifica-se a colisão com o elemento de fumaça
			return AIEvent::SMOKE;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::WALKING_SLOWLY){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(false){// Aqui verifica-se o fim da colisão com o elemento de fumaça
			return AIEvent::NOT_SMOKE;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::SENDING_BOMB){
		if(false){// Aqui verifica-se a colisão com o elemento estonteante
			return AIEvent::STUN;
		}
		else if(!path->empty()){
			return AIEvent::PATH_FREE;
		}
		else{return NONE;}
	}
	else if(actualState == AIState::STUNNED){
		if(false){// Aqui verifica-se o fim da colisão com o elemento estonteante
			return AIEvent::NOT_STUN;
		}
		else if(pathIndex == path->size()){
			return AIEvent::PATH_BLOCKED;
		}
		else{return NONE;}
	}
	return NONE;
}

void AIQuimic::Update(float dt){
	AIEvent actualTransition = ComputeEvents();
	actualState = dfa[actualState][actualTransition];
	bulletsCoolDown.Update(dt);
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
					float weight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);
				}
			}
			else if(vecSpeed.Magnitude() == 0.0){
				float weight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);
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
			tempDestination = Vec2(tileMap.GetTileSize().x * ((*path).at(pathIndex) % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path).at(pathIndex) / tileMap.GetWidth()));
			float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
			if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){
				associated.box.x = (tempDestination.x - (associated.box.w/2));
				associated.box.y = (tempDestination.y - (associated.box.h/2));
				pathIndex++;
				if(pathIndex != path->size()){
					tempDestination = Vec2(tileMap.GetTileSize().x * ((*path).at(pathIndex) % tileMap.GetWidth()),tileMap.GetTileSize().y*((*path).at(pathIndex) / tileMap.GetWidth()));
					float weight = tileWeightMap.at(tileMap.AtLayer((*path).at(pathIndex),WALKABLE_LAYER));
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
				}
			}
			else if(vecSpeed.Magnitude() == 0.0){
				float weight = tileWeightMap.at(tileMap.AtLayer((*path)[pathIndex],WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
			}
			else{
				associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
				associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);
			}
		}
	}
	else if(actualState == AIState::SENDING_BOMB){
		if(tileMap.GetCoordTilePos(Vec2(associated.box.x,associated.box.y), false, 0) != destTile){
			if(bulletsCoolDown.Get() > QUIMIC_MAX_BULLET_COOLDOWN){

				bulletsCoolDown.Restart();
				GameObject* target = tileMap.CloserObject(associated,std::string("Tower"));
				if(target != nullptr){
					Vec2 distance = associated.box.Center().VecDistance(target->box.Center());
					float angle = std::atan2(distance.y,distance.x);
					Bullet* bullet = new Bullet(associated.box.Center().x,associated.box.Center().y,angle,BULLET_VEL,BULLET_REACH,std::string("img/minionbullet2.png"),std::string("Tower"),3,0.1);
					Game::GetInstance().GetCurrentState().AddObject(bullet);
				}
			}
			
		}
		else{
			associated.RequestDelete();
			waveManager.NotifyEnemyGotToHisDestiny();
		}
	}
	else if(actualState == AIState::STUNNED){
		//Aqui executa animações do efeito estonteante
	}
	else{
		//Aqui executa animações de efeito de fumaça
	}
}

void AIQuimic::NotifyTileMapChanged(int tilePosition){
	if(path->end() != std::find( (path->begin())+pathIndex, path->end(), tilePosition)){
		Vec2 originCoord= associated.box.Center();
		path= GameResources::GetPath(((Enemy&)associated).GetType(), heuristic, tileMap.GetCoordTilePos(originCoord, false, 0), destTile, "map/WeightData.txt");
		pathIndex= 0;
	}
}

bool AIQuimic::Is(ComponentType type) const{
	return (type == ComponentType::AI_QUIMIC);
}
