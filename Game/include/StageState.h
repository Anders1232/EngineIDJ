#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <vector>
#include <memory>

#include "ActionManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "TileMap.h"
#include "Tileset.h"
#include "Timer.h"
#include "AIGoDown.h"
#include "AIPrintPath.h"

using std::vector;

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
		vector<vector<int>> *spawnGroups;
		Timer spawnTimer;
		void SpawnEnemy(int tileMapPosition);
};

#include "EndState.h"

#endif // STAGE_STATE_H
