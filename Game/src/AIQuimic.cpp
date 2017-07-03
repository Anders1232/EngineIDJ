#include "AIQuimic.h"

AIQuimic::AIQuimic(float speed, int dest, TileMap &tileMap, GameObject &associated):speed(speed),destTile(dest),tileMap(tileMap){

	heuristic = new ManhattanDistance();
	tileWeightMap = (*GameResources::GetWeightData("map/WeightData.txt")).at(((Enemy&)associated).GetType());
	path = tileMap.AStar(tileMap.GetTileMousePos(Vec2(associated.box.Center().x, associated.box.Center().y), false, 0),destTile,heuristic,tileWeightMap);
	vecSpeed = Vec2(0.0,0.0);

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

void AIQuimic::Update(GameObject &associated, float dt){

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
	else if(actualState == AIState::WALKING_SLOWLY){

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
					vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));
				}

			}
			else if(vecSpeed.Magnitude() == 0.0){

				float weight = tileWeightMap.at(tileMap.AtLayer(path.front(),WALKABLE_LAYER));
				vecSpeed = associated.box.Center().VecDistance(tempDestination).Normalize().MemberMult(speed / (weight * 2));

			}
			else{
			
				associated.box.x = (associated.box.Center().x + (vecSpeed.MemberMult(dt)).x - associated.box.w/2);
				associated.box.y = (associated.box.Center().y + (vecSpeed.MemberMult(dt)).y - associated.box.h/2);

			}
		}
	}
	else if(actualState == AIState::SENDING_BOMB){

		if(tileMap.GetTileMousePos(Vec2(associated.box.x,associated.box.y), false, 0) != destTile){

			//Executa aqui código para o inimigo jogar bombas no obstaculo mais próximo
			std::cout << "Entrou " << "Quimic " << destTile << " " << tileMap.GetTileMousePos(Vec2(associated.box.x,associated.box.y), false, 0) <<  std::endl;
			path = tileMap.AStar(tileMap.GetTileMousePos(Vec2(associated.box.Center().x,associated.box.Center().y), false, 0),destTile,heuristic,tileWeightMap);

		}
		else{associated.RequestDelete();}

	}
	else if(actualState == AIState::STUNNED){

		//Aqui executa animações do efeito estonteante

	}
	else{

		//Aqui executa animações de efeito de fumaça
		
	}

}

bool AIQuimic::Is(ComponentType type) const{
	return (type == ComponentType::AI_QUIMIC);
}
