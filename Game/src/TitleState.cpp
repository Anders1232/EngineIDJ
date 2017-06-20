#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState()
		: State()
		, UIcanvas({1024,600}, UIelement::BehaviorType::FIT)
		, bg("img/UI/main-menu/bg.png", UIelement::BehaviorType::STRETCH)
		, lua("img/UI/main-menu/lua.png", UIelement::BehaviorType::STRETCH)
		/*, nuvemA("img/UI/main-menu/nuvemA.png", UIelement::BehaviorType::STRETCH)*/
		, nuvemB("img/UI/main-menu/nuvemB.png", UIelement::BehaviorType::STRETCH)
		, icc("img/UI/main-menu/icc.png", UIelement::BehaviorType::STRETCH)
		, overlay("img/UI/main-menu/overlay.png", UIelement::BehaviorType::STRETCH)
		, title("img/UI/main-menu/title.png", UIelement::BehaviorType::FIT)
		, textGroup(UIelement::BehaviorType::STRETCH)
		, playText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Play")
		, editorText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Editor de Fases")
		, configText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Configuracoes")
		, exitText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Exit") {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();

	lua.SetSpriteScale(0.75);
	lua.SetAnchors( {(float)(0.5 - (lua.GetSpriteWidth()/2.+30.)/winSize.x), (float)(60./winSize.y)},
					{(float)(0.5 + (lua.GetSpriteWidth()/2.-30.)/winSize.x), (float)(60. + lua.GetSpriteHeight())/winSize.y } );
	nuvemB.SetSpriteScale(0.7);
	nuvemB.SetAnchors( {(float)(1. - (nuvemB.GetSpriteWidth()+110.)/winSize.x), (float)(70./winSize.y)},
					   {(float)(1. - 110./winSize.x), (float)(70.+nuvemB.GetSpriteHeight())/winSize.y } );
	icc.SetAnchors( {0., (float)(80./winSize.y)},
					{1., 1.});
	overlay.SetSpriteColorMultiplier({255,255,255}, 135);
	title.SetSpriteScale(0.7);
	title.SetAnchors( {(float)(0.5 - (title.GetSpriteWidth()/2.)/winSize.x), (float)(60./winSize.y)},
					  {(float)(0.5 + (title.GetSpriteWidth()/2.)/winSize.x), (float)(60. + title.GetSpriteHeight())/winSize.y } );
	textGroup.SetAnchors( {0.3, 0.45},
						  {0.7, 0.9} );
	playText.SetAnchors( {0., 0. },
					 	 {1., 0.25 } );
	editorText.SetAnchors( {0., 0.25},
						   {1., 0.5} );
	configText.SetAnchors( {0., 0.5},
						   {1., 0.75} );
	exitText.SetAnchors( {0., 0.75},
						 {1., 1.} );
}

void TitleState::Update(float dt) {
	if(ActionManager::StartAction()) {
		Game::GetInstance().Push(new StageState());
	} else if(InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	} else if(ActionManager::EscapeAction()) {
		popRequested = true;
	}

	// UI
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();
	Rect titleCanvas(0., 0., winSize.x, winSize.y);
	UIcanvas.Update(dt, titleCanvas);
	bg.Update(dt, UIcanvas);
	lua.Update(dt, UIcanvas);
	nuvemB.Update(dt, UIcanvas);
	icc.Update(dt, UIcanvas);
	overlay.Update(dt, UIcanvas);
	title.Update(dt, UIcanvas);
	textGroup.Update(dt, UIcanvas);
	playText.Update(dt, textGroup);
	editorText.Update(dt, textGroup);
	configText.Update(dt, textGroup);
	exitText.Update(dt, textGroup);
}

void TitleState::Render(void) const {
	// UI
	bg.Render();
	lua.Render();
	nuvemB.Render();
	icc.Render();
	overlay.Render();
	title.Render();
	playText.Render();
	editorText.Render();
	configText.Render();
	exitText.Render();
}

void TitleState::Pause(void) {}

void TitleState::Resume(void) {
	Camera::ForceZoom(1.0);
	Camera::pos = Vec2(0, 0);
}
