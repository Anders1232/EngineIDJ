#ifndef STATE_H
#define STATE_H

#include "Gameobject.h"
#include <vector>
#include <memory>

class State
{
	public:
		State(void);
		virtual ~State(void);
		virtual void Update(float dt)=0;
		virtual void Render(void) const =0;
		virtual void Pause(void)=0;
		virtual void Resume(void)=0;
		virtual void AddObject(GameObject *object);
		bool PopRequested(void);
		bool QuitRequested(void);
	protected:
		virtual void UpdateArray(float dt);
		virtual void RenderArray(void);
		bool popRequested;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif // STATE_H
