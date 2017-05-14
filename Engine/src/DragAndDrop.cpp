#include "DragAndDrop.h"
#include "InputManager.h"
#include "Camera.h"
#include "Error.h"

DragAndDrop::DragAndDrop(bool dragging)
	:isDragging(dragging)
{
}

void DragAndDrop::Update(GameObject &associated)
{
	InputManager &inputManager= InputManager::GetInstance();
	
	if((false == isDragging) )
	{
		//\todo ver se o zoom interfere aqui
		Vec2 worldMousePos= inputManager.GetMousePos()+ Camera::pos;
		//std::cout << WHERE << "associated.GetWorldRenderedRect()= {" << associated.GetWorldRenderedRect().x, associated.GetWorldRenderedRect().y;
		if(worldMousePos.IsInRect(associated.GetWorldRenderedRect()))
		{
			TEMP_REPORT_I_WAS_HERE;
			isDragging= true;
		}
	}
	if(isDragging)
	{
		Vec2 mousePos= inputManager.GetMousePos();
		associated.box= mousePos+Camera::pos;
		if(inputManager.MouseRelease(RIGHT_MOUSE_BUTTON))
			isDragging=false;

	}
}

bool DragAndDrop::Is(ComponentType type) const
{
	return (ComponentType::DRAG_AND_DROP == type);
}
