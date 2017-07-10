#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "EndStateData.h"
#include "GameObject.h"
#include "Music.h"
#include "Rect.h"
#include "Sprite.h"
#include "Text.h"
#include "UIcanvas.h"
#include "UIimage.h"
#include "UItext.h"
#include "UItextButton.h"
#include "UIverticalGroup.h"
#include "Vec2.h"

#define END_STATE_FONT_SIZE (40)
#define END_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128

class EndState: public State {
	public:
		EndState(EndStateData stateData);
		void Update(float dt);
		void Render() const;
		void Pause();
		void Resume();
		void StartLoop(void);
		void LoadAssets(void) const;
	private:
		void SetupUI(EndStateData stateData);
		void UpdateUI(float dt);
		void RenderUI(void) const;
		void Close(void);
		void MainMenu(void);
		Music music;
		Music intro;

		UIcanvas HUDcanvas;
		UIimage bg;
		UItext venceuText;
		UIverticalGroup optionsGroup;
		UItextButton playBtn;
		UItextButton exitBtn;
};

#endif // ENDSTATE_H
