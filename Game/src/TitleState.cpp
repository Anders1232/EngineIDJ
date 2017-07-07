#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

#define DISABLED_COLOR		{ 70, 70, 70,100} // Dark Gray
#define ENABLED_COLOR		{164,133,166,255} // Purple
#define HIGHLIGHTED_COLOR	{227,196,230,255} // Purple-ish white
#define PRESSED_COLOR		{227,196,230,255} // Purple-ish white

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
		, optionsGroup()
		, playBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Jogar")
		, editorBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Editor de Fases", UIbutton::State::DISABLED)
		, configBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, std::string("Configura") + (char)0xE7 /*ç*/ + (char)0xF5 /*õ*/ + "es", UIbutton::State::DISABLED)
		, exitBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Sair")
		, titleMusic("audio/trilha_sonora/main_title_.ogg"){

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
	
	playBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	playBtn.SetClickCallback( this, [] (void* caller) {
									Game::GetInstance().Push(new StageState());
								} );
	
	editorBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	
	configBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	
	exitBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	exitBtn.SetClickCallback( this, [] (void* caller) {
									TitleState* titleState = static_cast<TitleState*>(caller);
									titleState->Exit();
								} );

	optionsGroup.groupedElements.push_back(&playBtn);
	optionsGroup.groupedElements.push_back(&editorBtn);
	optionsGroup.groupedElements.push_back(&configBtn);
	optionsGroup.groupedElements.push_back(&exitBtn);
	titleMusic.Play(2);
}

void TitleState::Update(float dt) {
	if(INPUT_MANAGER.QuitRequested()) {
		quitRequested = true;
	}

	UpdateUI(dt);
}

void TitleState::Render(void) const {
	RenderUI();
}

void TitleState::RenderUI(void) const {
	bg.Render();
	lua.Render();
	nuvemB.Render();
	icc.Render();
	overlay.Render();
	title.Render();
	// optionsGroup.Render();
	playBtn.Render();
	editorBtn.Render();
	configBtn.Render();
	exitBtn.Render();
}

void TitleState::Pause(void) {}

void TitleState::Resume(void) {
	Camera::ForceLogZoom(0.0);
	Camera::pos = Vec2(0, 0);
}

void TitleState::UpdateUI(float dt) {
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);
	canvas.Update(dt, winSize);
	bg.Update(dt, canvas);
	lua.Update(dt, canvas);
	nuvemB.Update(dt, canvas);
	icc.Update(dt, canvas);
	overlay.Update(dt, canvas);
	title.Update(dt, canvas);
	optionsGroup.Update(dt, canvas);
	playBtn.Update(dt, optionsGroup);
	editorBtn.Update(dt, optionsGroup);
	configBtn.Update(dt, optionsGroup);
	exitBtn.Update(dt, optionsGroup);
}

void TitleState::Exit() {
	popRequested = true;
}

void TitleState::LoadAssets(void) const{
	Resources::GetImage("img/title.jpg");
	Resources::GetImage("img/UI/main-menu/bg.png");
	Resources::GetImage("img/UI/main-menu/lua.png");
	Resources::GetImage("img/UI/main-menu/nuvemB.png");
	Resources::GetImage("img/UI/main-menu/icc.png");
	Resources::GetImage("img/UI/main-menu/overlay.png");
	Resources::GetImage("img/UI/main-menu/title.png");
	Resources::GetMusic("audio/trilha_sonora/main_title_.ogg");
	Resources::GetFont("font/SHPinscher-Regular.otf", 95);
}
