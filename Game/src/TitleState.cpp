#include "TitleState.h"

#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

#include <cfloat>

#define ECLIPSE_DURATION	6.5 // s
#define OVERLAY_FADEIN_DURATION	4 // s
#define MAX_SPEED			20 // px/s
#define MIN_SPEED			5 // px/s
#define DISABLED_COLOR		{ 70, 70, 70,100} // Dark Gray
#define ENABLED_COLOR		{164,133,166,255} // Purple
#define HIGHLIGHTED_COLOR	{227,196,230,255} // Purple-ish white
#define PRESSED_COLOR		{227,196,230,255} // Purple-ish white

TitleState::TitleState()
		: State()
		, speedNuvemA(std::rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED)
		, speedNuvemB(std::rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED)
		, introTimer()
		, clickSound("audio/Interface/Click1.wav")
		, canvas({1024,600}, UIelement::BehaviorType::STRETCH)
		, bg("img/UI/main-menu/bg.png", UIelement::BehaviorType::STRETCH)
		, lua("img/UI/main-menu/spritesheetlua.png", ECLIPSE_DURATION/8., 8, UIelement::BehaviorType::FIT)
		, nuvemA("img/UI/main-menu/nuvemA.png", UIelement::BehaviorType::FILL)
		, nuvemB("img/UI/main-menu/nuvemB.png", UIelement::BehaviorType::FILL)
		, icc("img/UI/main-menu/icc.png", UIelement::BehaviorType::STRETCH)
		, overlay("img/UI/main-menu/overlay.png", UIelement::BehaviorType::STRETCH)
		, title("img/UI/main-menu/SpriteSheetTitle.png", 1./5., 5, UIelement::BehaviorType::FIT)
		, optionsGroup()
		, playBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Jogar")
		, editorBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Editor de Fases", UIbutton::State::DISABLED)
		, configBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, std::string("Configura") + (char)0xE7 /*ç*/ + (char)0xF5 /*õ*/ + "es", UIbutton::State::DISABLED)
		, exitBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Sair")
		, titleMusic("audio/trilha_sonora/main_title_.ogg") {
	Resources::ChangeMusicVolume(0);
	Resources::ChangeSoundVolume(0);
	introTimer.Restart();
	finishedEclipse = false;
	finishedFadeIn = false;
	forceEnd = false;
	
	SetupUI();
}

void TitleState::SetupUI(void) {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();

	lua.GetSprite().SetScale(0.75);
	lua.SetAnchors( {(float)(0.5 - (lua.GetSprite().GetWidth()/2.+30.)/winSize.x), (float)(60./winSize.y)},
					{(float)(0.5 + (lua.GetSprite().GetWidth()/2.-30.)/winSize.x), (float)(60. + lua.GetSprite().GetHeight())/winSize.y } );
	
	nuvemA.SetCenter({0.5, 0.1});
	nuvemA.GetSprite().SetScale(0.6);
	nuvemA.SetAnchors( {0., (float)20./winSize.y},
					   {(float)nuvemA.GetSprite().GetWidth()/winSize.x, (float)(20.+nuvemA.GetSprite().GetHeight())/winSize.y } );

	nuvemB.GetSprite().SetScale(0.7);
	nuvemB.SetAnchors( {(float)(1. - (nuvemB.GetSprite().GetWidth()+110.)/winSize.x), (float)(70./winSize.y)},
					   {(float)(1. - 110./winSize.x), (float)(70.+nuvemB.GetSprite().GetHeight())/winSize.y } );
	
	icc.SetAnchors( {0., (float)(80./winSize.y)},
					{1., 1.});
	
	overlay.GetSprite().colorMultiplier = {255,255,255,0};
	
	title.GetSprite().SetScale(0.7);
	title.SetAnchors( {(float)(0.5 - (title.GetSprite().GetWidth()/2.)/winSize.x), (float)(60./winSize.y)},
					  {(float)(0.5 + (title.GetSprite().GetWidth()/2.)/winSize.x), (float)(60. + title.GetSprite().GetHeight())/winSize.y } );
	
	optionsGroup.SetAnchors( {0.3, 0.45},
							 {0.7, 0.9} );
	
	playBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	playBtn.SetClickCallback( this, [] (void* caller) {
									TitleState* titleState = static_cast<TitleState*>(caller);
									titleState->Play();
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

	titleMusic.Play(0);
}

void TitleState::Update(float dt) {
	if(INPUT_MANAGER.QuitRequested()) {
		quitRequested = true;
	}
	if(INPUT_MANAGER.KeyRelease(ESCAPE_KEY)) {
		forceEnd = true;
	}

	introTimer.Update(dt);
	if(forceEnd || (!finishedEclipse && introTimer.Get() >= ECLIPSE_DURATION)) {
		finishedEclipse = true;
		lua.GetSprite().SetFrameTime(FLT_MAX);
		lua.GetSprite().SetFrame(7);
		Color c = overlay.GetSprite().colorMultiplier;
		c.a = 180;
		overlay.GetSprite().colorMultiplier = c;
		introTimer.Restart();
	}
	if(forceEnd || (finishedEclipse && ! finishedFadeIn && introTimer.Get() >= OVERLAY_FADEIN_DURATION)) {
		finishedFadeIn = true;
		Color c = title.GetSprite().colorMultiplier;
		c.a = 255;
		title.GetSprite().colorMultiplier = c;
		introTimer.Restart();
	}
	forceEnd = false;

	UpdateUI(dt);
}

void TitleState::UpdateUI(float dt) {
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);

	if(!finishedEclipse) {
		Color c = overlay.GetSprite().colorMultiplier;
		overlay.GetSprite().colorMultiplier = {c.r, c.g, c.b, (unsigned char)(180*introTimer.Get()/ECLIPSE_DURATION)};
	}

	if(finishedEclipse && !finishedFadeIn) {
		Color c = title.GetSprite().colorMultiplier;
		c.a = 255*introTimer.Get()/OVERLAY_FADEIN_DURATION;
		title.GetSprite().colorMultiplier = c;
	}

	canvas.Update(dt, winSize);
	bg.Update(dt, canvas);
	lua.Update(dt, canvas);
	nuvemA.Update(dt, canvas);
	nuvemB.Update(dt, canvas);
	icc.Update(dt, canvas);
	overlay.Update(dt, canvas);
	title.Update(dt, canvas);
	optionsGroup.Update(dt, canvas);
	playBtn.Update(dt, optionsGroup);
	editorBtn.Update(dt, optionsGroup);
	configBtn.Update(dt, optionsGroup);
	exitBtn.Update(dt, optionsGroup);

	MoveClouds(dt);
}

void TitleState::MoveClouds(float dt) {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();

	Rect box = nuvemA;
	Rect offsets = nuvemA.GetOffsets();
	if (box.x + box.w < 0) {
		offsets.x += winSize.x + nuvemA.GetSprite().GetWidth();
		offsets.w += winSize.x + nuvemA.GetSprite().GetWidth();
		speedNuvemA = std::rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
	}
	nuvemA.SetOffsets( {offsets.x-dt*speedNuvemA, offsets.y}, {offsets.w-dt*speedNuvemA, offsets.h});

	box = nuvemB;
	offsets = nuvemB.GetOffsets();
	if (box.x + box.w < 0) {
		offsets.x += winSize.x + nuvemB.GetSprite().GetWidth();
		offsets.w += winSize.x + nuvemB.GetSprite().GetWidth();
		speedNuvemB = std::rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
	}
	nuvemB.SetOffsets( {offsets.x-dt*speedNuvemB, offsets.y}, {offsets.w-dt*speedNuvemB, offsets.h});
}

void TitleState::Render(void) const {
	RenderUI();
}

void TitleState::RenderUI(void) const {
	bg.Render();
	lua.Render();
	nuvemA.Render();
	nuvemB.Render();
	icc.Render();
	overlay.Render();
	if(finishedEclipse) {
		title.Render();
		if(finishedFadeIn) {
			// optionsGroup.Render(true);
			playBtn.Render();
			editorBtn.Render();
			configBtn.Render();
			exitBtn.Render();
		}
	}
}

void TitleState::Pause(void) {
}

void TitleState::Resume(void) {
	Camera::ForceLogZoom(0.0);
	Camera::pos = Vec2(0, 0);
}

void TitleState::Play(void) {
	clickSound.Play(1);
	Game::GetInstance().Push(new StageState());
}

void TitleState::Exit() {
	clickSound.Play(1);
	popRequested = true;
}

void TitleState::LoadAssets(void) const{
	Resources::GetImage("img/title.jpg");
	Resources::GetImage("img/UI/main-menu/bg.png");
	Resources::GetImage("img/UI/main-menu/lua.png");
	Resources::GetImage("img/UI/main-menu/nuvemA.png");
	Resources::GetImage("img/UI/main-menu/nuvemB.png");
	Resources::GetImage("img/UI/main-menu/icc.png");
	Resources::GetImage("img/UI/main-menu/overlay.png");
	Resources::GetImage("img/UI/main-menu/title.png");
	Resources::GetMusic("audio/trilha_sonora/main_title_.ogg");
	Resources::GetMusic("audio/Interface/Click1.wav");
	Resources::GetFont("font/SHPinscher-Regular.otf", 95);
}
