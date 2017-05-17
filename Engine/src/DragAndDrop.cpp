#include "DragAndDrop.h"
#include "InputManager.h"
#include "Camera.h"
#include "Error.h"

DragAndDrop::DragAndDrop(TileMap *map, bool dragging, bool dragOnActionHold)
	:isDragging(dragging), dragOnHold(dragOnActionHold), tileMap(map){
}

void DragAndDrop::Update(GameObject &associated)
{
	InputManager &inputManager= InputManager::GetInstance();
	
<<<<<<< HEAD
	if((false == isDragging) )
	{
		//\todo ver se o zoom interfere aqui
		Vec2 worldMousePos= inputManager.GetMousePos()+ Camera::pos;
		//std::cout << WHERE << "associated.GetWorldRenderedRect()= {" << associated.GetWorldRenderedRect().x, associated.GetWorldRenderedRect().y;
=======
/*	if(inputManager.MousePress(RIGHT_MOUSE_BUTTON) && (false == isDragging) )
	{
		//\todo ver se o zoom interfere aqui
		Vec2 worldMousePos= inputManager.GetMousePos()+ Camera::pos;
//		std::cout << WHERE << "associated.GetWorldRenderedRect()= {" << associated.GetWorldRenderedRect().x << ", " << associated.GetWorldRenderedRect().y << ", " << associated.GetWorldRenderedRect().w << ", " << associated.GetWorldRenderedRect().h << "}\n";
>>>>>>> 2aac11ffd701451ed408a8874746ee23f760feca
		if(worldMousePos.IsInRect(associated.GetWorldRenderedRect()))
		{
			TEMP_REPORT_I_WAS_HERE;
			isDragging= true;
		}
	}
*/	if(isDragging && inputManager.IsMouseDown(RIGHT_MOUSE_BUTTON))
	{
		Vec2 mousePos= inputManager.GetMousePos();
		associated.box= mousePos+Camera::pos-Vec2(associated.box.w/2, associated.box.h/2);
	}
	else if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON))
	{
		tileMap->InsertGO(&associated);
		isDragging= false;
	}
}

bool DragAndDrop::Is(ComponentType type) const
{
	return (ComponentType::DRAG_AND_DROP == type);
}