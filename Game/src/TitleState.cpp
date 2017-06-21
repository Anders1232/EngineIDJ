#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState()
		: State()
		, canvas({1024,600}, UIelement::BehaviorType::STRETCH)
		, bg("img/UI/main-menu/bg.png", UIelement::BehaviorType::STRETCH)
		, lua("img/UI/main-menu/lua.png", UIelement::BehaviorType::FIT)
		/*, nuvemA("img/UI/main-menu/nuvemA.png", UIelement::BehaviorType::FILL)*/
		, nuvemB("img/UI/main-menu/nuvemB.png", UIelement::BehaviorType::FILL)
		, icc("img/UI/main-menu/icc.png", UIelement::BehaviorType::STRETCH)
		, overlay("img/UI/main-menu/overlay.png", UIelement::BehaviorType::STRETCH)
		, title("img/UI/main-menu/title.png", UIelement::BehaviorType::FIT)
		, optionsGroup(UIelement::BehaviorType::STRETCH)
		, playText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Play")
		, editorText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Editor de Fases", UIbutton::State::DISABLED)
		, configText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Configuracoes", UIbutton::State::DISABLED)
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
	overlay.SetSpriteColorMultiplier({255,255,255,135});
	title.SetSpriteScale(0.7);
	title.SetAnchors( {(float)(0.5 - (title.GetSpriteWidth()/2.)/winSize.x), (float)(60./winSize.y)},
					  {(float)(0.5 + (title.GetSpriteWidth()/2.)/winSize.x), (float)(60. + title.GetSpriteHeight())/winSize.y } );
	optionsGroup.SetAnchors( {0.3, 0.45},
						  {0.7, 0.9} );
	playText.ConfigColors( { 70, 70, 70,100},
						   {164,133,166,255},
						   {227,196,230,255} );
	playText.SetClickCallback( this, [] (void* caller) {
									Game::GetInstance().Push(new StageState());
								} );
	playText.SetAnchors( {0., 0. },
					 	 {1., 0.25 } );
	editorText.ConfigColors( { 70, 70, 70,100},
						  	 {164,133,166,255},
						  	 {227,196,230,255} );
	editorText.SetAnchors( {0., 0.25},
						   {1., 0.5} );
	configText.ConfigColors( { 70, 70, 70,100},
						  	 {164,133,166,255},
						  	 {227,196,230,255} );
	configText.SetAnchors( {0., 0.5},
						   {1., 0.75} );
	exitText.ConfigColors( { 70, 70, 70,100},
						   {164,133,166,255},
						   {227,196,230,255} );
	exitText.SetClickCallback( this, [] (void* caller) {
									TitleState* titleState = static_cast<TitleState*>(caller);
									titleState->Exit();
								} );
	exitText.SetAnchors( {0., 0.75},
						 {1., 1.} );
}

void TitleState::Update(float dt) {
	if(INPUT_MANAGER.QuitRequested()) {
		quitRequested = true;
	}

	UpdateUI(dt);
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
	Camera::ForceLogZoom(0.0);
	Camera::pos = Vec2(0, 0);
}

void TitleState::UpdateUI(float dt) {
	Vec2 mousePos = INPUT_MANAGER.GetMousePos();

	if(playText.GetUIbuttonState() != UIbutton::State::DISABLED) {
		if(mousePos.IsInRect(playText.GetBoundingBox())) {
			playText.SetUIbuttonState(UIbutton::State::HIGHLIGHTED);
			if(INPUT_MANAGER.MouseRelease(LEFT_MOUSE_BUTTON)) {
				playText.Click();
			}
		} else {
			playText.SetUIbuttonState(UIbutton::State::ENABLED);
		}
	}

	if(editorText.GetUIbuttonState() != UIbutton::State::DISABLED) {
		if(mousePos.IsInRect(editorText.GetBoundingBox())) {
			editorText.SetUIbuttonState(UIbutton::State::HIGHLIGHTED);
			if(INPUT_MANAGER.MouseRelease(LEFT_MOUSE_BUTTON)) {
				editorText.Click();
			}
		} else {
			editorText.SetUIbuttonState(UIbutton::State::ENABLED);
		}
	}

	if(configText.GetUIbuttonState() != UIbutton::State::DISABLED) {
		if(mousePos.IsInRect(configText.GetBoundingBox())) {
			configText.SetUIbuttonState(UIbutton::State::HIGHLIGHTED);
			if(INPUT_MANAGER.MouseRelease(LEFT_MOUSE_BUTTON)) {
				configText.Click();
			}
		} else {
			configText.SetUIbuttonState(UIbutton::State::ENABLED);
		}
	}

	if(exitText.GetUIbuttonState() != UIbutton::State::DISABLED) {
		if(mousePos.IsInRect(exitText.GetBoundingBox())) {
			exitText.SetUIbuttonState(UIbutton::State::HIGHLIGHTED);
			if(INPUT_MANAGER.MouseRelease(LEFT_MOUSE_BUTTON)) {
				exitText.Click();
			}
		} else {
			exitText.SetUIbuttonState(UIbutton::State::ENABLED);
		}
	}


	Vec2 winSize = Game::GetInstance().GetWindowDimensions();
	Rect titleCanvas(0., 0., winSize.x, winSize.y);
	canvas.Update(dt, titleCanvas);
	bg.Update(dt, canvas);
	lua.Update(dt, canvas);
	nuvemB.Update(dt, canvas);
	icc.Update(dt, canvas);
	overlay.Update(dt, canvas);
	title.Update(dt, canvas);
	optionsGroup.Update(dt, canvas);
	playText.Update(dt, optionsGroup);
	editorText.Update(dt, optionsGroup);
	configText.Update(dt, optionsGroup);
	exitText.Update(dt, optionsGroup);
}

void TitleState::Exit() {
	popRequested = true;
}
