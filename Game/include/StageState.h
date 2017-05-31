#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "GameObject.h"
#include "Tileset.h"
#include "TileMap.h"
#include "InputManager.h"
#include "State.h"
#include "Music.h"
#include "DragAndDrop.h"


class StageState: public State {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
	private:
		Sprite bg;
		TileMap *tileMap;
		TileSet tileSet;
		InputManager &inputManager;
		Music music;
};

#include "EndState.h"

#endif // STAGE_STATE_H
