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
#include "Tower.h"
#include "WaveManager.h"
#include "UIcanvas.h"
#include "UIimageButton.h"
#include "UIgridGroup.h"
#include "UItext.h"
#include "UIverticalGroup.h"

using std::vector;

#define TOWERNAME_DEFAULT_TEXT " "
#define TOWERCOST_DEFAULT_TEXT " "
#define TOWERDAMAGE_DEFAULT_TEXT " "
#define TOWERDAMGETYPE_DEFAULT_TEXT " "

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
		void SetupUI(void);
		void UpdateUI(float dt);
		void RenderUI(void) const;
		void ToggleMenu(void);
		void SetTowerInfoData(string name = TOWERNAME_DEFAULT_TEXT,
							  string cost = TOWERCOST_DEFAULT_TEXT,
							  string damage = TOWERDAMAGE_DEFAULT_TEXT,
							  string damageType = TOWERDAMGETYPE_DEFAULT_TEXT
		);
		void CreateTower(Tower::TowerType towerType);
		TileSet tileSet;
		TileMap tileMap;/**< Mapa de tiles do jogo. */
		InputManager &inputManager;
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

		UIverticalGroup towerInfoGroup;
		UItext towerName;
		UItext towerCost;
		UItext towerDamage;
		UItext towerDamageType;

		UIgridGroup towersBtnGroup;
		UIimageButton towerBtn1;
		UIimageButton towerBtn2;
		UIimageButton towerBtn3;
		UIimageButton towerBtn4;

		UIcanvas health;
		UIimage healthIcon;
		UIimage healthbarBg;
		UIimage healthbarBar;

		UIcanvas wave;
		UIimage waveIcon;
		UIimage wavebarBg;
		UIimage wavebarBar;
};

#include "EndState.h"

#endif // STAGE_STATE_H
