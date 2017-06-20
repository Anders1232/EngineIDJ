#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "ActionManager.h"
#include "Image.h"
#include "Canvas.h"
#include "UItext.h"
#include "State.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
	private:
		Canvas UIcanvas;
		Image bg;
		Image lua;
		// Image nuvemA;
		Image nuvemB;
		Image icc;
		Image overlay;
		Image title;
		Canvas textGroup;
		UItext playText;
		UItext editorText;
		UItext configText;
		UItext exitText;
};

#endif // TITLESTATE_H
