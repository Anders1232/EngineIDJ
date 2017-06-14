#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"

DragAndDrop::DragAndDrop(TileMap *map, bool dragOnActionHold)
		: dragOnHold(dragOnActionHold), tileMap(map) {
}

void DragAndDrop::Update(GameObject &associated, float dt) {
	InputManager &inputManager= InputManager::GetInstance();

	if(inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)){

		tileMap->RemoveGO(&associated);

	} else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
		tileMap->InsertGO(&associated);
		associated.RemoveComponent(DRAG_AND_DROP);

	}
}

bool DragAndDrop::Is(ComponentType type) const {
	return ComponentType::DRAG_AND_DROP == type;
}
