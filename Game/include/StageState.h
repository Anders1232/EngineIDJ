#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <vector>
#include <memory>

#include "ActionManager.h"
#include "DragAndDrop.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "TileMap.h"
#include "Tileset.h"
#include "Timer.h"
#include "WaveManager.h"

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
		void ShowLightning(float dt);
	private:
		Sprite bg;
		TileSet tileSet;
		TileMap tileMap;
		InputManager &inputManager;
		Music music;
		vector<vector<int>> *spawnGroups;
		bool isLightning;
		Timer lightningTimer;
		Color lightningColor;
		WaveManager waveManager;
		GameObject nullGameObject;
		vector<int> waves;//vetor de waves a ser lido no arquivo
		void SpawnEnemy(int tileMapPosition);
};

#include "EndState.h"

#endif // STAGE_STATE_H
