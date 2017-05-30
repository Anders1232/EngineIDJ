#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "Gameobject.h"
#include "Tileset.h"
#include "TileMap.h"
#include "InputManager.h"
#include "ActionManager.h"
#include "State.h"
#include "Music.h"

#define NUMBER_OF_ALIENS (6)

//#define BG_POINTER

class StageState: public State
{
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
		void CreateAlien();
};

#include "EndState.h"

#endif // STAGE_STATE_H
