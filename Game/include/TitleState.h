#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Sprite.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void NewRender(void) const;
		void Render(void) const;
		void Pause(void);
		void Resume(void);
	private:
		Sprite bg;
};

#endif // TITLESTATE_H
