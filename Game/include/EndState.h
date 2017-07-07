#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "EndStateData.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Text.h"
#include "UIcanvas.h"
#include "UIimage.h"
#include "Rect.h"

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
		void SetupUI(void);
		void UpdateUI(float dt);
		void RenderUI(void) const;
		UIcanvas HUDcanvas;
		UIimage bg;
		Music music;
		Music intro;
		Text instruction;
};

#endif // ENDSTATE_H
