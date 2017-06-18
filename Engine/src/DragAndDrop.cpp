#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"

DragAndDrop::DragAndDrop(TileMap *map, bool dragging, bool dragOnActionHold)
	: isDragging(dragging), dragOnHold(dragOnActionHold), tileMap(map) {
}

void DragAndDrop::Update(GameObject &associated, float dt) {
	InputManager &inputManager= InputManager::GetInstance();
	

	if(isDragging && inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)) {
		Vec2 mousePos = Camera::ScreenToWorld(inputManager.GetMousePos());
		associated.box = mousePos-Vec2(associated.box.w/2, associated.box.h/2);
	} else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON) && isDragging) {
		tileMap->InsertGO(&associated);
		isDragging = false;
	}
}

bool DragAndDrop::Is(ComponentType type) const {
	return ComponentType::DRAG_AND_DROP == type;
}
