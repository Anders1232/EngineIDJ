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
#include "AIGoDown.h"
#include "AIPrintPath.h"
#include "WaveManager.h"
#include "Obstacle.h"
#include "NearestGOFinder.h"

using std::vector;

class StageState: public State, public TileMapObserver, public NearestGOFinder {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void ShowLightning(float dt);
		void NotifyTileMapChanged(int tilePosition);
		GameObject* FindNearestGO(Vec2 origin, std::string targetType, float range= std::numeric_limits<float>::max());
	private:
		TileSet tileSet;
		TileMap tileMap;/**< Mapa de tiles do jogo. */
		InputManager &inputManager;
		Music music;
		
		bool isLightning;
		Timer lightningTimer;
		Color lightningColor;
		float lightningInterval;

		WaveManager *waveManager;/**< Referencia para a WaveManager, gerenciador de waves. Essa Referência existe aqui por motivos de perfornance, para não ter que procurá-lo todo Update.*/
		vector<int> waves;//vetor de waves a ser lido no arquivo
		void InitializeObstacles(void);
		std::vector<std::unique_ptr<Obstacle>> obstacleArray;
		void AddObstacle(Obstacle *obstacle);
		void RenderObstacleArray(void) const;

		int frameRateCounter;
		Timer frameRateTimer;
};

#include "EndState.h"

#endif // STAGE_STATE_H
