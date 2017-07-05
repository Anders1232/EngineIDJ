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
#include "PlayerData.h"
#include "UIcanvas.h"
#include "UIimageButton.h"
#include "UIgridGroup.h"
#include "UIverticalGroup.h"
#include "Obstacle.h"

using std::vector;

class StageState: public State, public TileMapObserver {
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void) const;
		void Pause(void);
		void Resume(void);
		void ShowLightning(float dt);
		void NotifyTileMapChanged(int tilePosition);
	private:
		void UpdateUI(float dt);
		void RenderUI(void) const;
		void ToggleMenu(void);
		TileSet tileSet;
		TileMap tileMap;/**< Mapa de tiles do jogo. */
		InputManager &inputManager;
		PlayerData &playerData;/**< Armazena os dados do jogador e os exibe em tela. */

		Music music;
		
		bool isLightning;
		Timer lightningTimer;
		Color lightningColor;
		WaveManager *waveManager;/**< Referencia para a WaveManeger, gerenciador de waves. Essa Referência existe aqui por motivos de perfornance, para não ter que procurá-lo todo Update.*/
		vector<int> waves;//vetor de waves a ser lido no arquivo

		bool menuIsShowing;
		
		UIcanvas HUDcanvas;
		UIimage menuBg;
		UIimageButton openMenuBtn;
		UIgridGroup towersBtnGroup;
		UIimageButton towerBtn1;
		UIimageButton towerBtn2;
		UIimageButton towerBtn3;
		UIimageButton towerBtn4;

		UIverticalGroup towerInfoGroup;
		float lightningInterval;

		void InitializeObstacles(void);
		std::vector<std::unique_ptr<Obstacle>> obstacleArray;
		void AddObstacle(Obstacle *obstacle);
		void RenderObstacleArray(void) const;

		int frameRateCounter;
		Timer frameRateTimer;
};

#include "EndState.h"

#endif // STAGE_STATE_H
