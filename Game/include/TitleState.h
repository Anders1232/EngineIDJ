#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "ActionManager.h"
#include "Rect.h"
#include "UIimage.h"
#include "UIcanvas.h"
#include "UItext.h"
#include "UItextButton.h"
#include "UIverticalGroup.h"
#include "State.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void Exit(void);
	private:
		void UpdateUI(float dt);
		void RenderUI() const;
		UIcanvas canvas;
		UIimage bg;
		UIimage lua;
		// UIimage nuvemA;
		UIimage nuvemB;
		UIimage icc;
		UIimage overlay;
		UIimage title;
		UIverticalGroup optionsGroup;
		UItextButton playText;
		UItextButton editorText;
		UItextButton configText;
		UItextButton exitText;
};

#endif // TITLESTATE_H
