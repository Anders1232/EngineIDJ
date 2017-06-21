#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "ActionManager.h"
#include "UIimage.h"
#include "UIcanvas.h"
#include "UItext.h"
#include "UIbutton.h"
#include "State.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
	private:
		UIcanvas canvas;
		UIimage bg;
		UIimage lua;
		// UIimage nuvemA;
		UIimage nuvemB;
		UIimage icc;
		UIimage overlay;
		UIimage title;
		UIcanvas optionsGroup;
		UItext playText;
		UItext editorText;
		UItext configText;
		UItext exitText;
};

#endif // TITLESTATE_H
