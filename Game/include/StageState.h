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
#include "PlayerData.h"
#include "UIcanvas.h"
#include "UIimageButton.h"
#include "UIgridGroup.h"

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
		void UpdateUI(float dt);
		void RenderUI(void) const;
		void ToggleMenu(void);
		TileSet tileSet;
		TileMap tileMap;/**< Mapa de tiles do jogo. */
		InputManager &inputManager;
		Music music;
		bool isLightning;
		Timer lightningTimer;
		Color lightningColor;
		WaveManager *waveManager;/**< Referencia para a WaveManeger, gerenciador de waves. Essa Referência existe aqui por motivos de perfornance, para não ter que procurá-lo todo Update.*/
		PlayerData *playerBoard;/**< Armazena os dados do jogador e os exibe em tela. */
		vector<int> waves;//vetor de waves a ser lido no arquivo

		bool menuIsShowing;
		
		UIcanvas HUDcanvas;
		UIimageButton openMenuBtn;
		UIimage menuBg;
		UIgridGroup towersBtnGroup;
		UIimageButton towerBtn1;
};

#include "EndState.h"

#endif // STAGE_STATE_H
