#ifndef ENDDTATE_H
#define ENDDTATE_H

#include "GameObject.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "EndStateData.h"

#define END_STATE_FONT_SIZE (40)
#define END_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128

class EndState: public State {
	public:
		EndState(EndStateData stateData);
		void Update(float dt);
		void Render() const;
		void Pause();
		void Resume();
	private:
		Sprite bg;
		Music music;
		Text instruction;
};

#include "InputManager.h"
#include "StageState.h"

#endif // ENDDTATE_H
