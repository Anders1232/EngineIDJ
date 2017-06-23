#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"

<<<<<<< HEAD
DragAndDrop::DragAndDrop(TileMap *map,GameObject &associated,bool dragging, bool dragOnActionHold)
	: isDragging(dragging), dragOnHold(dragOnActionHold), tileMap(map),associated(associated) {
=======
DragAndDrop::DragAndDrop(TileMap &map,Vec2 associatedInitialPos, bool redrag, bool dragOnActionHold)
		: dragOnHold(dragOnActionHold),associatedInitialPos(associatedInitialPos), tileMap(map), redrag(redrag) {
>>>>>>> a3fd237d23ea080d695000cc63486c2d1c2fdfed
}

void DragAndDrop::Update(float dt) {
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)){
		Vec2 mousePos= Camera::ScreenToWorld(inputManager.GetMousePos() );
		associated.box= mousePos-Vec2(associated.box.w/2, associated.box.h/2);
	} 
	else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
		if(redrag){
			tileMap.InsertGO(&associated, associatedInitialPos);
		}
		else{
			tileMap.InsertGO(&associated);
		}
		associated.RemoveComponent(DRAG_AND_DROP);
	}
}

bool DragAndDrop::Is(ComponentType type) const {
	return ComponentType::DRAG_AND_DROP == type;
}
