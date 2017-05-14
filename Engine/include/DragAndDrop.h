#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "Component.h"

class DragAndDrop : public Component
{
	public:
		DragAndDrop(bool dragging= false);
		void Update(GameObject &associated);
		bool Is(ComponentType) const;
	private:
		bool isDragging;
};

#endif // DRAGANDDROP_H
