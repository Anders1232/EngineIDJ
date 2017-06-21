#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "EndStateData.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Text.h"

#define END_STATE_FONT_SIZE (40)
#define END_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128

class EndState: public State {
	public:
		EndState(EndStateData stateData);
		void Update(float dt);
		void Render() const;
		void Pause();
		void Resume();
		void LoadAssets(void);
	private:
		Sprite bg;
		Music music;
		Text instruction;
};

#include "InputManager.h"
#include "StageState.h"

#endif // ENDSTATE_H
