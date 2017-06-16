#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState() : State(), bg("img/title.jpg") {}

void TitleState::Update(float dt) {
	if(ActionManager::StartAction()) {
		Game::GetInstance().Push(new StageState());
	} else if(InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	} else if(ActionManager::EscapeAction()) {
		popRequested = true;
	}
}

void TitleState::Render(void) const {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();
	bg.Render(Rect(0., 0., winSize.x, winSize.y));
}

void TitleState::Pause(void) {}

void TitleState::Resume(void) {
	Camera::ForceZoom(1.0);
	Camera::pos = Vec2(0, 0);
}
