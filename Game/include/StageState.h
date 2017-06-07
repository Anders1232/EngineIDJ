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
#include "Timer.h"

using std::vector;

class StageState: public State {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void NewRender(void) const;
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
