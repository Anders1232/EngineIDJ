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
		void ShowLightning(float dt);
	private:
		Sprite bg;/**< Referencia para a Sprite de fundo de tela. */
		TileSet tileSet;
		TileMap tileMap;/**< Referencia para o mapa de tiles do jogo. */
		InputManager &inputManager;
		Music music;
		bool isLightning;
		Timer lightningTimer;
		Color lightningColor;
		WaveManager *waveManager;/**< Referencia para a WaveManeger, gerenciador de waves. */
		vector<int> waves;//vetor de waves a ser lido no arquivo
};

#include "EndState.h"

#endif // STAGE_STATE_H
