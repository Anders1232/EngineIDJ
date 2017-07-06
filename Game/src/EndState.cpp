#include "EndState.h"
#include "InputManager.h"
#include "StageState.h"
#include "Camera.h"

EndState::EndState(EndStateData stateData)
		: bg( (stateData.playerVictory) ? "img/UI/end-game/prototipo-menu-vitoria.png" : "img/UI/end-game/prototipo-menu-derrota.png")
		, music( (stateData.playerVictory) ? "audio/endStateWin.ogg" : "audio/endStateLose.ogg")
		, instruction("font/SHPinscher-Regular.otf",
					END_STATE_FONT_SIZE,
					BLENDED,
					{255, 80, 80, 255},
					true) {
	music.Play(0);
	instruction.SetText("Press Space to go to menu or Esc to close the game");
	instruction.SetTimeShown(0.6);
	instruction.SetStrobeFrequency(1.0);

	Vec2 pos = Game::GetInstance().GetWindowDimensions();
	instruction.SetPos(0, pos.y-instruction.GetSize().y, true);
}

void EndState::Update(float dt) {
	instruction.Update(dt);
	InputManager &inputManager = InputManager::GetInstance();
	if(inputManager.QuitRequested()) {
		quitRequested = true;
	}
	if(ActionManager::EscapeAction()) {
		quitRequested =true;
	}
	if(ActionManager::StartAction()) {
		popRequested = true;
	}
}

void EndState::Render() const {
	bg.Render(Rect(0,0,0,0), 0 , false);
	instruction.Render();
}

void EndState::Pause() {}

void EndState::Resume() {
	Camera::ForceLogZoom(0.0);
	Camera::pos = Vec2(0, 0);
}
