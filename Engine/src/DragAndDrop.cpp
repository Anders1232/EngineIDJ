#include "DragAndDrop.h"

DragAndDrop::DragAndDrop()
	:isDragging(false)
{
	
}

bool DragAndDrop::Is(ComponentType type) const
{
	return (ComponentType::DRAG_AND_DROP == type);
}
