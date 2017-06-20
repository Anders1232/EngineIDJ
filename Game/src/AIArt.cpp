#include "AIArt.h"

//AIState{WALKING,WAITING,FINDINGHEALTH,STUNNED};
//AIEvent{PATH_BLOCKED,PATH_FREE,FOUNDHEALTH,STUN,NOT_STUN}; 

AIArt::AIArt(float speed,int dest,TileMap* tilemap,GameObject &associated):speed(speed),destTile(dest),tilemap(tilemap),associated(associated){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	path = tilemap->AStar(tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0),destTile,heuristic,tileWeightMap);

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

		if(tilemap->Stun(associated.box)){

			return AIEvent::STUN;

		}
		if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}

	}
	else if(actualState == AIState::WAITING){
		//std::cout <<"chegou 1" << std::endl;
		if(tilemap->Stun(associated.box)){

			return AIEvent::STUN;

		}
		if(!path.empty()){

			std::cout << AIEvent::PATH_FREE << std::endl;
			return AIEvent::PATH_FREE;

		}

	}
	else if(actualState == AIState::STUNNED){

		if(!tilemap->Stun(associated.box)){

			return AIEvent::NOT_STUN;

		}
		if(path.empty()){

			return AIEvent::PATH_BLOCKED;

		}

	}

	return NONE;
	
}

void AIArt::Update(float dt){

	std::cout << "Transição atual: " << ComputeEvents() << std::endl;
	std::cout << "Estado atual: " << actualState << std::endl;
	actualState = dfa[actualState][ComputeEvents()];
	std::cout << "Tamanho do caminho: " << path.size() << std::endl;
	if(actualState == AIState::WALKING){

		float lastDistance = associated.box.Center().VecDistance(tempDestination).Magnitude();
		float weight = tileWeightMap.at(tilemap->AtLayer(path.front(),WALKABLE_LAYER));
		vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / weight);

		if((vecSpeed * dt).Magnitude() >= lastDistance){

			associated.box.x = (tempDestination.x - (associated.box.w/2));
			associated.box.y = (tempDestination.y - (associated.box.h/2));
			tempDestination = Vec2(path.front() / tilemap->GetWidth(),path.front() % tilemap->GetWidth());
			path.pop_front();

		}
		else{

			associated.box.x = (associated.box.Center().x + (vecSpeed * dt).x - associated.box.w/2);
			associated.box.y = (associated.box.Center().y + (vecSpeed * dt).y - associated.box.h/2);

		}
	}
	else if(actualState == AIState::WAITING){

		if(path.front() != destTile){
			path = tilemap->AStar(tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0),destTile,heuristic,tileWeightMap);
		}
	}
	else{

		//Aqui executa animações do efeito estonteante

	}

}

bool AIArt::Is(ComponentType type) const{
	return (type == ComponentType::AI_ART);
}
