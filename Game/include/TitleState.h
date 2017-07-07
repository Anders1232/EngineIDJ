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
#include "Sound.h"
#include "Music.h"

class TitleState: public State {
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void Play(void);
		void Exit(void);
		void LoadAssets(void) const;
	private:
		void SetupUI(void);
		void UpdateUI(float dt);
		void RenderUI() const;

		Sound clickSound;

		UIcanvas canvas;
		UIimage bg;
		UIimage lua;
		UIimage nuvemA;
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
