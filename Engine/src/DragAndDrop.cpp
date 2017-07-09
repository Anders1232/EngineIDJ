#include "DragAndDrop.h"

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"
#include "TileMap.h"

DragAndDrop::DragAndDrop(TileMap &map,Vec2 associatedInitialPos, GameObject &associated, bool redrag, bool dragOnActionHold)
			: dragOnHold(dragOnActionHold)
			, associatedInitialPos(associatedInitialPos)
			, tileMap(map)
			, redrag(redrag)
			, associated(associated)
			, dragNDrop("audio/Acoes/Consertando1.wav") {
}

void DragAndDrop::Update(float dt) {
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
		bool success = false;
		if(redrag) {
			if(associated.Is("Tower")){
				associated.box = associated.box+Vec2(associated.box.w/4, (associated.box.h-60) );
				success = tileMap.InsertGO(&associated, associatedInitialPos);
				associated.box = associated.box-Vec2(associated.box.w/4, (associated.box.h-60) );
			}
			else{
				success = tileMap.InsertGO(&associated, associatedInitialPos);
			}
			if(!success) {
				int tileIndex = tileMap.GetCoordTilePos(associatedInitialPos, false, 0);
				int line = tileIndex / tileMap.GetWidth();
				int column = tileIndex % tileMap.GetWidth();
				Vec2 tileSize = tileMap.GetTileSize();
				Vec2 pos = Vec2(column*tileSize.x, line*tileSize.y) - Vec2(associated.box.w/4, (associated.box.h-60) );
				associated.box = Rect(pos.x, pos.y, associated.box.w, associated.box.h);
			}
		}
		else {
			if(associated.Is("Tower")){
				associated.box = associated.box+Vec2(associated.box.w/4, (associated.box.h-60) );
				success = tileMap.InsertGO(&associated, true);
				associated.box = associated.box-Vec2(associated.box.w/4, (associated.box.h-60) );
			}
			else{
				success = tileMap.InsertGO(&associated, true);
			}
			if(!success) { return; }
		}
		if(success) { dragNDrop.Play(1); }
		associated.RemoveComponent(DRAG_AND_DROP);
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
