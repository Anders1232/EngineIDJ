#include "EndState.h"
#include "InputManager.h"
#include "StageState.h"
#include "Camera.h"

#include "Game.h"

#include <string>

#define COLOR_WIN		{183,156,245,255}
#define COLOR_LOSE		{132,132,132,100}

#define DISABLED_COLOR		{ 70, 70, 70,100} // Dark Gray
#define ENABLED_COLOR		{183,156,245,255} // Purple
#define HIGHLIGHTED_COLOR	{227,196,230,255} // Purple-ish white
#define PRESSED_COLOR		{227,196,230,255} // Purple-ish white

// QUE GAMBIARRA ABSURDA D:
void StartFinalLoop() {
	static_cast<EndState&>(Game::GetInstance().GetCurrentState()).StartLoop();
}

EndState::EndState(EndStateData stateData)
		: music("audio/tela_de_vitoria_derrota/loop_tela_vitoria_derrota.ogg")
		, intro( (stateData.playerVictory) ? "audio/tela_de_vitoria_derrota/vitoria.ogg" : "audio/tela_de_vitoria_derrota/derrota.ogg")
		, HUDcanvas()
		, bg( (stateData.playerVictory) ? "img/UI/end-game/win.jpg" : "img/UI/end-game/lose.jpg")
		, venceuText("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, COLOR_WIN, stateData.playerVictory ? std::string("Vit") + (char)0xF3 /*ó*/ + "ria" : "Derrota")
		, optionsGroup()
		, playBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Menu Principal")
		, exitBtn("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, {255,255,255,255}, "Sair") {
	Resources::ChangeMusicVolume(0);
	Resources::ChangeSoundVolume(0);

	intro.Play(1);
	Mix_HookMusicFinished(StartFinalLoop);

	SetupUI(stateData);
}

void EndState::SetupUI(EndStateData stateData) {
	bg.GetSprite().colorMultiplier = {255, 255, 255, 200};

	venceuText.SetAnchors( {0.2, 0.},
						   {0.8, 0.4});
	if( stateData.playerVictory) {
		venceuText.SetColor( COLOR_WIN );
	} else {
		venceuText.SetColor( COLOR_LOSE );
	}

	optionsGroup.padding = 30.;
	optionsGroup.SetAnchors( {0.15, 0.5},
							 {0.85, 0.8});
	optionsGroup.groupedElements.push_back(&playBtn);
	optionsGroup.groupedElements.push_back(&exitBtn);

	playBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	playBtn.SetClickCallback( this, [] (void* caller) {
									EndState* endState = static_cast<EndState*>(caller);
									endState->MainMenu();
								} );

	exitBtn.ConfigColors(DISABLED_COLOR, ENABLED_COLOR, HIGHLIGHTED_COLOR, PRESSED_COLOR);
	exitBtn.SetClickCallback( this, [] (void* caller) {
									EndState* endState = static_cast<EndState*>(caller);
									endState->Close();
								} );
}

void EndState::Update(float dt) {
	if(INPUT_MANAGER.QuitRequested()) {
		quitRequested = true;
	}

	UpdateUI(dt);
}

void EndState::UpdateUI(float dt) {
	Rect winSize = Rect(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);

	HUDcanvas.Update(dt, winSize);
	bg.Update(dt, HUDcanvas);
	venceuText.Update(dt, HUDcanvas);
	optionsGroup.Update(dt, HUDcanvas);
	playBtn.Update(dt, optionsGroup);
	exitBtn.Update(dt, optionsGroup);
}

void EndState::Render() const {
	RenderUI();
}

void EndState::RenderUI() const {
	bg.Render();
	venceuText.Render();
	optionsGroup.Render();
	playBtn.Render();
	exitBtn.Render();
}

void EndState::Pause() {}

void EndState::Resume() {
	Camera::ForceLogZoom(0.0);
	Camera::pos = Vec2(0, 0);
}

void EndState::StartLoop() {
	music.Play(0);
	Mix_HookMusicFinished(NULL);
}

void EndState::LoadAssets(void) const{
	Resources::GetImage("img/UI/end-game/win.jpg");
	Resources::GetImage("img/UI/end-game/lose.jpg");
	Resources::GetFont("font/SHPinscher-Regular.otf", 32);
	Resources::GetMusic("audio/tela_de_vitoria_derrota/vitoria.ogg");
	Resources::GetMusic("audio/tela_de_vitoria_derrota/derrota.ogg");
	Resources::GetMusic("audio/tela_de_vitoria_derrota/loop_tela_vitoria_derrota.ogg");
}

void EndState::Close(void) {
	quitRequested = true;
}

void EndState::MainMenu(void) {
	popRequested = true;
}
