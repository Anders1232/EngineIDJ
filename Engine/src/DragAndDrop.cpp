#include "DragAndDrop.h"

DragAndDrop::DragAndDrop()
	:isDragging(false)
{
	
}

void DragAndDrop::Update(GameObject &associated)
{
	
}

bool DragAndDrop::Is(ComponentType type) const
{
	return (ComponentType::DRAG_AND_DROP == type);
}
