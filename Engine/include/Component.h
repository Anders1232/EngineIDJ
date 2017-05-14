#ifndef COMPONENT_H
#define COMPONENT_H

#include "Gameobject.h"

enum ComponentType
{
	DRAG_AND_DROP=0,
	SIZE
};

#ifndef GAME_OBJECT
class GameObject;
#endif

#define COMPONENT
class Component
{
	public:
		virtual void Update(GameObject &associated)=0;
		virtual bool Is(ComponentType) const =0;
};

#endif
