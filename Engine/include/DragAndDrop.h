#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include "Component.h"
#include "TileMap.h"

class DragAndDrop : public Component
{
	public:
		DragAndDrop(TileMap *map, bool dragging= false, bool dragOnActionHold= true);
		void Update(GameObject &associated);
		bool Is(ComponentType) const;
	private:
		bool isDragging;
		bool dragOnHold;
		TileMap *tileMap;
};

#endif // DRAGANDDROP_H
