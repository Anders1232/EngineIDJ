#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"

DragAndDrop::DragAndDrop(TileMap *map,Vec2 associatedInitialPos, bool dragOnActionHold)
		: dragOnHold(dragOnActionHold),associatedInitialPos(associatedInitialPos), tileMap(map) {
}

void DragAndDrop::Update(GameObject &associated, float dt) {
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)){
		Vec2 mousePos= inputManager.GetMousePos()*(1/Camera::GetZoom());
		associated.box= mousePos+Camera::pos-Vec2(associated.box.w/2, associated.box.h/2);
	} 
	else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)){
		tileMap->InsertGO(&associated,associatedInitialPos);
		associated.RemoveComponent(DRAG_AND_DROP);
	}
}

bool DragAndDrop::Is(ComponentType type) const {
	return ComponentType::DRAG_AND_DROP == type;
}
