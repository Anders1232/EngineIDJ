#include "AIQuimic.h"

AIQuimic::AIQuimic(float speed,int dest,TileMap* tilemap,GameObject &associated):speed(speed),destTile(dest),tilemap(tilemap),associated(associated){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt"))[((Enemy&)associated).GetType()];
	path = tilemap->AStar(tilemap->GetTileMousePos(Vec2(((Enemy&)associated).box.x,((Enemy&)associated).box.y), false, 0),destTile,heuristic,tileWeightMap);

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
}

AIQuimic::AIEvent AIQuimic::ComputeEvents(){

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
	else if(actualState == AIState::SENDING_BOMB){

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

void AIQuimic::Update(float dt){

}

bool AIQuimic::Is(ComponentType type) const{
	return (type == ComponentType::AI_QUIMIC);
}