#include "AIMedic.h"

AIMedic::AIMedic(float speed,int dest,TileMap* tilemap,GameObject &associated):speed(speed),destTile(dest),tilemap(tilemap),associated(associated){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	path = tilemap->AStar(tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0),destTile,heuristic,tileWeightMap);

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
}

AIMedic::AIEvent AIMedic::ComputeEvents(){

	if(actualState == AIState::WALKING){

		if(false){// Aqui verifica-se a colisão com o elemento estonteante

			return AIEvent::STUN;

		}
		else if(path.empty()){

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
		else if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}
		else{return NONE;}

	}
	else if(actualState == AIState::WAITING){

		if(false){// Aqui verifica-se a colisão com o elemento estonteante

			return AIEvent::STUN;

		}
		else if(path.back() == destTile){

			//std::cout << "PATH_FREE" << std::endl;
			return AIEvent::PATH_FREE;

		}
		else{return NONE;}

	}
	else if(actualState == AIState::STUNNED){

		if(false){// Aqui verifica-se o fim da colisão com o elemento estonteante

			return AIEvent::NOT_STUN;

		}
		else if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}
		else{return NONE;}

	}

	return NONE;
	
}

void AIMedic::Update(float dt){
	//enum AIState{WALKING,WALKING_SLOWLY,WAITING,STUNNED,STATE_NUM};
	//enum AIEvent{NONE,PATH_BLOCKED,PATH_FREE,SMOKE,NOT_SMOKE,STUN,NOT_STUN,EVENT_NUM}; 

	AIEvent actualTransition = ComputeEvents();
	//std::cout << "Estado atual: " << actualState << std::endl;
	//std::cout << "Transição atual : " << actualTransition << std::endl;
	actualState = dfa[actualState][actualTransition];

	if(actualState == AIState::WALKING){

		tempDestination = Vec2(tilemap->GetTileSize().x * (path.front() % tilemap->GetWidth()),tilemap->GetTileSize().y*(path.front() / tilemap->GetWidth()));
		float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
		float weight = tileWeightMap.at(tilemap->AtLayer(path.front(),WALKABLE_LAYER));
		vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);

		if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){
			associated.box.x = (tempDestination.x - (associated.box.w/2));
			associated.box.y = (tempDestination.y - (associated.box.h/2));
			tempDestination = Vec2(path.front() / tilemap->GetWidth(),path.front() % tilemap->GetWidth());
			path.pop_front();

		}
		else{
		
			associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
			associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);

		}
	}
	else if(actualState == AIState::WALKING_SLOWLY){

		tempDestination = Vec2(tilemap->GetTileSize().x * (path.front() % tilemap->GetWidth()),tilemap->GetTileSize().y*(path.front() / tilemap->GetWidth()));
		float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
		float weight = tileWeightMap.at(tilemap->AtLayer(path.front(),WALKABLE_LAYER));
		vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
		
		if((vecSpeed.MemberMult(dt)).Magnitude() >= lastDistance){
			associated.box.x = (tempDestination.x - (associated.box.w/2));
			associated.box.y = (tempDestination.y - (associated.box.h/2));
			tempDestination = Vec2(path.front() / tilemap->GetWidth(),path.front() % tilemap->GetWidth());
			path.pop_front();

		}
		else{
		
			associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
			associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);

		}
	}
	else if(actualState == AIState::WAITING){

		path = tilemap->AStar(tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0),destTile,heuristic,tileWeightMap);
		
	}
	else if(actualState == AIState::STUNNED){

		//Aqui executa animações do efeito estonteante

	}
	else{

		//Aqui executa animações de efeito de fumaça

	}

}

bool AIMedic::Is(ComponentType type) const{
	return (type == ComponentType::AI_MEDIC);
}