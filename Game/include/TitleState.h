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
#include "Music.h"

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

		UItextButton playBtn;
		UItextButton editorBtn;
		UItextButton configBtn;
		UItextButton exitBtn;
		Music titleMusic;
};

#endif // TITLESTATE_H
