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
#include "WaveManager.h"
#include "EmptyGameObject.h"
using std::vector;

class StageState: public State {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void LoadAssets(void);
	private:
		Sprite bg;
		TileSet tileSet;
		TileMap tileMap;
		InputManager &inputManager;
		Music music;
		vector<vector<int>> *spawnGroups;
		//Timer spawnTimer;
		void SpawnEnemy(int tileMapPosition);
		WaveManager waveManager;
		EmptyGameObject nullGameObject;
		vector<int> waves;//vetor de waves a ser lido no arquivo
};

#include "EndState.h"

#endif // STAGE_STATE_H
