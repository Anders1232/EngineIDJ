#include "AIArt.h"

//AIState{WALKING,WAITING,FINDINGHEALTH,STUNNED};
//AIEvent{PATH_BLOCKED,PATH_FREE,FOUNDHEALTH,STUN,NOT_STUN}; 

AIArt::AIArt(float speed,int dest,TileMap* tilemap):speed(speed),destTile(dest),tilemap(tilemap){

	heuristic = new ManhattanDistance();

	dfa[AIState::WALKING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WALKING][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::WALKING][AIEvent::NONE] = AIState::WALKING;

	dfa[AIState::WAITING][AIEvent::STUN] = AIState::STUNNED;
	dfa[AIState::WAITING][AIEvent::PATH_FREE] = AIState::WALKING;
	dfa[AIState::WAITING][AIEvent::NONE] = AIState::WAITING;

	dfa[AIState::STUNNED][AIEvent::NOT_STUN] = AIState::WALKING;
	dfa[AIState::STUNNED][AIEvent::PATH_BLOCKED] = AIState::WAITING;
	dfa[AIState::STUNNED][AIEvent::NONE] = AIState::STUNNED;

	actualState = AIState::WAITING;
}

AIArt::AIEvent AIArt::ComputeEvents(GameObject &associated){

	if(actualState == AIState::WALKING){

		if(tilemap->Stun(associated.box)){

			return AIEvent::STUN;

		}
		if(path.empty()){
			float position = tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0);
			std::map<int, double> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
			path = tilemap->AStar(position,destTile,heuristic,weightMap);
			if(path.empty() && position != destTile){

				return AIEvent::PATH_BLOCKED;

			}

		}
	}
	else if(actualState == AIState::WAITING){

		if(tilemap->Stun(associated.box)){

			return AIEvent::STUN;

		}

		float position = tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0);
		std::map<int, double> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];

		if(!tilemap->AStar(position,destTile,heuristic,weightMap).empty()){

			return AIEvent::PATH_FREE;

		}

	}
	else if(actualState == AIState::STUNNED){

		if(!tilemap->Stun(associated.box)){

			return AIEvent::NOT_STUN;

		}
		if(path.empty()){
			float position = tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0);
			std::map<int, double> weightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
			path = tilemap->AStar(position,destTile,heuristic,weightMap);
			if(path.empty()){

				return AIEvent::PATH_BLOCKED;

			}
		}

	}

	return NONE;
	
}

void AIArt::Update(GameObject &associated, float dt){

	actualState = dfa[actualState][ComputeEvents(associated)];
	if(actualState)
	associated.box.y+= speed*dt;

}

bool AIArt::Is(ComponentType type) const{
	return (type == ComponentType::AI_ART);
}
