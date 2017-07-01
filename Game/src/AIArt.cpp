#include "AIArt.h"

//enum AIState{WALKING,WAITING,STUNNED,STATE_NUM};
//enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,STUN,NOT_STUN,EVENT_NUM}; 

AIArt::AIArt(float speed,int dest,TileMap &tileMap,GameObject &associated):speed(speed),destTile(dest),tileMap(tileMap){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	path = tileMap.AStar(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0),destTile,heuristic,tileWeightMap);
	vecSpeed = Vec2(0.0,0.0);

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
}

AIArt::AIEvent AIArt::ComputeEvents(){

	if(actualState == AIState::WALKING){

		if(false){// Aqui verifica-se a colisão com o elemento estonteante

			return AIEvent::STUN;

		}
		else if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}
		else{return NONE;}

	}
	else if(actualState == AIState::WAITING){

		if(false){// Aqui verifica-se a colisão com o elemento estonteante

			return AIEvent::STUN;

		}
		else if(!path.empty()){

			//std::cout << "PATH_FREE" << std::endl;
			return AIEvent::PATH_FREE;

		}
		else{return NONE;}

	}
	else if(actualState == AIState::STUNNED){

		if(false){// Aqui verifica-se a colisão com o elemento estonteante

			return AIEvent::NOT_STUN;

		}
		else if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}
		else{return NONE;}

	}

	return NONE;
	
}

void AIArt::Update(GameObject &associated, float dt){

	AIEvent actualTransition = ComputeEvents();
	actualState = dfa[actualState][actualTransition];

	if(actualState == AIState::WALKING){

		if(!path.empty()){

			tempDestination = Vec2(tileMap.GetTileSize().x * (path.front() % tileMap.GetWidth()),tileMap.GetTileSize().y*(path.front() / tileMap.GetWidth()));
			float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();

			if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){

				associated.box.x = (tempDestination.x - (associated.box.w/2));
				associated.box.y = (tempDestination.y - (associated.box.h/2));
				path.pop_front();

				if(!path.empty()){

					tempDestination = Vec2(tileMap.GetTileSize().x * (path.front() % tileMap.GetWidth()),tileMap.GetTileSize().y*(path.front() / tileMap.GetWidth()));
					float weight = tileWeightMap.at(tileMap.AtLayer(path.front(),WALKABLE_LAYER));
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);
				}

			}
			else if(vecSpeed.Magnitude() == 0.0){

				float weight = tileWeightMap.at(tileMap.AtLayer(path.front(),WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);

			}
			else{
			
				associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
				associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);

			}
		}
	}
	else if(actualState == AIState::WAITING){

		if(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0) != destTile){
			std::cout << "Entrou" << "art"<< destTile << " " << tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0) <<  std::endl;
			path = tileMap.AStar(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0),destTile,heuristic,tileWeightMap);

		}
	}
	else{

		//Aqui executa animações do efeito estonteante

	}

}

bool AIArt::Is(ComponentType type) const{
	return (type == ComponentType::AI_ART);
}
