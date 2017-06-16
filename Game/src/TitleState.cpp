#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState()
		: State()
		, bg("img/UI/main-menu/bg.png", UIelement::BehaviorType::STRETCH)
		, lua("img/UI/main-menu/lua.png", UIelement::BehaviorType::STRETCH)
		, nuvemB("img/UI/main-menu/nuvemB.png", UIelement::BehaviorType::STRETCH)
		/*, nuvemA("img/UI/main-menu/nuvemA.png", UIelement::BehaviorType::STRETCH)*/
		, icc("img/UI/main-menu/icc.png", UIelement::BehaviorType::STRETCH) {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();

	lua.SetSpriteScale(0.75);
	lua.SetOffsets( { (winSize.x - lua.GetSpriteWidth())/2-30, 60.},
					{-(winSize.x + lua.GetSpriteWidth())/2-30, (float)-(60.+lua.GetSpriteHeight())} );
	nuvemB.SetSpriteScale(0.7);
	nuvemB.SetOffsets( {winSize.x - nuvemB.GetSpriteWidth()-110, 70.},
					   {-110., (float)(-(winSize.y - nuvemB.GetSpriteHeight())+70.)});
	icc.SetOffsets( {0., 80.},
					{0., 0.});
}

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
	Rect titleCanvas(0., 0., winSize.x, winSize.y);
	bg.Render(titleCanvas);
	lua.Render(titleCanvas);
	nuvemB.Render(titleCanvas);
	icc.Render(titleCanvas);
}

void TitleState::Pause(void) {}

void TitleState::Resume(void) {
	Camera::ForceZoom(1.0);
	Camera::pos = Vec2(0, 0);
}
