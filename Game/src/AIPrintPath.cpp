#include "AIPrintPath.h"

AIPrintPath::AIPrintPath(int dest):dest(dest){
}

void AIPrintPath::Update(GameObject &associated){

	if(Enemy& e = dynamic_cast<Enemy&>(associated)){

		
		
	}

}

bool AIPrintPath::Is(ComponentType type) const{
	return (type == ComponentType::AI_PRINT_PATH);
}