#include "DragAndDrop.h"
#include "InputManager.h"
#include "Camera.h"
#include "Error.h"

DragAndDrop::DragAndDrop(TileMap *map, bool dragging, bool dragOnActionHold)
	:isDragging(dragging), dragOnHold(dragOnActionHold), tileMap(map){
}

void DragAndDrop::Update(GameObject &associated){
	InputManager &inputManager= InputManager::GetInstance();
	
/*	if(inputManager.MousePress(RIGHT_MOUSE_BUTTON) && (false == isDragging) ){
		//\todo ver se o zoom interfere aqui
		Vec2 worldMousePos= inputManager.GetMousePos()+ Camera::pos;
		REPORT_DEBUG("associated.GetWorldRenderedRect()= {" << associated.GetWorldRenderedRect().x << ", " << associated.GetWorldRenderedRect().y << ", " << associated.GetWorldRenderedRect().w << ", " << associated.GetWorldRenderedRect().h << "}");
		if(worldMousePos.IsInRect(associated.GetWorldRenderedRect())){
			TEMP_REPORT_I_WAS_HERE;
			isDragging= true;
			tileMap->GetTileMousePos(associated.box.Center(), true, 0);
//			tileMap->
		}
	}
*/	if(isDragging && inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON)){
		Vec2 mousePos= inputManager.GetMousePos()*(1/Camera::GetZoom());
		associated.box= mousePos+Camera::pos-Vec2(associated.box.w/2, associated.box.h/2);
	}
	else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON) && isDragging){
		tileMap->InsertGO(&associated);
		isDragging= false;
	}
}

bool DragAndDrop::Is(ComponentType type) const{
	return (ComponentType::DRAG_AND_DROP == type);
}
