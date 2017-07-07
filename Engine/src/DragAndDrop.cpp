#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"
#include "TileMap.h"

DragAndDrop::DragAndDrop(TileMap &map,Vec2 associatedInitialPos, GameObject &associated, bool redrag, bool dragOnActionHold)
		: dragOnHold(dragOnActionHold),associatedInitialPos(associatedInitialPos), tileMap(map), redrag(redrag), associated(associated)
, dragNDrop("audio/Acoes/Consertando1.wav"){
}

void DragAndDrop::Update(float dt) {
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
		if(redrag) {
			if(associated.Is("Tower")){
				associated.box = associated.box+Vec2(associated.box.w/4, (associated.box.h-60) );
				tileMap.InsertGO(&associated, associatedInitialPos);
				associated.box = associated.box-Vec2(associated.box.w/4, (associated.box.h-60) );
			}
			else{
				tileMap.InsertGO(&associated, associatedInitialPos);
			}
		}
		else {
			if(associated.Is("Tower")){
				associated.box = associated.box+Vec2(associated.box.w/4, (associated.box.h-60) );
				tileMap.InsertGO(&associated, associatedInitialPos);
				associated.box = associated.box-Vec2(associated.box.w/4, (associated.box.h-60) );
			}
			else{
				tileMap.InsertGO(&associated);
			}
		}
		associated.RemoveComponent(DRAG_AND_DROP);
		dragNDrop.Play(1);
	} else if(inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON) || !dragOnHold) {
		Vec2 mousePos= Camera::ScreenToWorld(inputManager.GetMousePos() );
		if(associated.Is("Tower")){
			associated.box= mousePos-Vec2(associated.box.w/2, associated.box.h);
		}
		else{
			associated.box= mousePos-Vec2(associated.box.w/2, associated.box.h/2);
		}
	}
}

bool DragAndDrop::Is(ComponentType type) const {
	return ComponentType::DRAG_AND_DROP == type;
}
