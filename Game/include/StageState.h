#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "GameObject.h"
#include "Tileset.h"
#include "TileMap.h"
#include "InputManager.h"
#include "ActionManager.h"
#include "State.h"
#include "Music.h"
#include "Timer.h"
#include "WaveManager.h"
#include "EmptyGameObject.h"
using std::vector;

/**
	\todo Fazer com que o tileMap n~ao seja mais um ponteiro.


*/
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
		TileSet tileSet;
		TileMap tileMap; //*tileMap
		InputManager &inputManager;
		Music music;
		vector<vector<int>> *spawnGroups;
		Timer spawnTimer;
		void SpawnEnemy(int tileMapPosition);
		WaveManager waveManager;
		EmptyGameObject nullGameObject;
		
};

#include "EndState.h"

#endif // STAGE_STATE_H
