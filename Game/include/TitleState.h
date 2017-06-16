#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "ActionManager.h"
#include "UIelement.h"
#include "State.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
	private:
		UIelement bg;
		UIelement lua;
		// UIelement nuvemA;
		UIelement nuvemB;
		UIelement icc;
};

#endif // TITLESTATE_H
