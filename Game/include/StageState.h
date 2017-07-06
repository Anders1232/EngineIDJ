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
#include "Obstacle.h"
#include "Sound.h"

using std::vector;

class StageState: public State {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void ShowLightning(float dt);
	private:
		TileSet tileSet;
		TileMap tileMap;/**< Mapa de tiles do jogo. */
		InputManager &inputManager;
		Music music;
		bool isLightning;
		bool isThundering;
		Timer lightningTimer;
		Color lightningColor;

		WaveManager *waveManager;/**< Referencia para a WaveManager, gerenciador de waves. Essa Referência existe aqui por motivos de perfornance, para não ter que procurá-lo todo Update.*/

		void InitializeObstacles(void);
		std::vector<std::unique_ptr<Obstacle>> obstacleArray;
		void AddObstacle(Obstacle *obstacle);
		void RenderObstacleArray(void) const;
		Sound nightSound;
		Sound thunderSound;

		int frameRateCounter;
		Timer frameRateTimer;
};

#include "EndState.h"

#endif // STAGE_STATE_H
