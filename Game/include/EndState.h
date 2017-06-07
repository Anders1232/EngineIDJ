#ifndef ENDDTATE_H
#define ENDDTATE_H

#include "GameObject.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "EndStateData.h"

#define END_STATE_FONT_SIZE (40)

class EndState: public State {
	public:
		EndState(EndStateData stateData);
		void Update(float dt);
		void Render() const;
		void NewRender() const;
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
