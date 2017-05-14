#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentType
{
	DRAG_AND_DROP=0,
	SIZE
};

class Component
{
	public:
		virtual void Update()=0;
		virtual bool Is(ComponentType) const =0;
};

#endif
