#include "EndState.h"

#include "Camera.h"

EndState::EndState(EndStateData stateData)
		: bg( (stateData.playerVictory) ? "img/win.jpg" : "img/lose.jpg")
		, music( (stateData.playerVictory) ? "audio/endStateWin.ogg" : "audio/endStateLose.ogg")
		, instruction("font/Call me maybe.ttf",
					  END_STATE_FONT_SIZE,
					  BLENDED,
					  {255, 255, 255, 255},
					  true) {
	music.Play(0);
	instruction.SetText("Press Esc to go to menu or Space to play again!");
	instruction.SetTimeShown(0.6);
	instruction.SetStrobeFrequency(1.0);

	Vec2 pos = Game::GetInstance().GetWindowDimensions();
	if(stateData.playerVictory) {
		instruction.SetPos(0, pos.y*0.005, true);
	}
	else {
		instruction.SetPos(0, pos.y-instruction.GetSize().y, true);
	}
}

void EndState::Update(float dt) {
	instruction.Update(dt);
	InputManager &inputManager = InputManager::GetInstance();

	if(inputManager.QuitRequested()) {
		quitRequested = true;
	}
	if(ActionManager::EscapeAction()) {
		popRequested =true;
	}
	if(ActionManager::StartAction()) {
		popRequested = true;
		Game::GetInstance().Push(new StageState());
	}
}

void EndState::Render() const {
	bg.Render(Rect(0,0,0,0), 0 , false);
	instruction.Render();
}

void EndState::Pause() {}

void EndState::Resume() {
	Camera::ForceZoom(1.0);
	Camera::pos = Vec2(0, 0);
}

void EndState::LoadAssets(void){
	Resources::GetImage("img/win.jpg");
	Resources::GetImage("img/lose.jpg");
	Resources::GetFont("font/Call me maybe.ttf", 32);
	Resources::GetMusic("audio/endStateWin.ogg");
	Resources::GetMusic("audio/endStateLose.ogg");
}