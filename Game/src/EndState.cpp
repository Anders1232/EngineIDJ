#include "EndState.h"
#include "InputManager.h"
#include "StageState.h"
#include "Camera.h"

#include "Game.h"

// QUE GAMBIARRA ABSURDA D:
void StartFinalLoop() {
	static_cast<EndState&>(Game::GetInstance().GetCurrentState()).StartLoop();
}

EndState::EndState(EndStateData stateData)
		: bg( (stateData.playerVictory) ? "img/UI/end-game/prototipo-menu-vitoria.png" : "img/UI/end-game/prototipo-menu-derrota.png")
		, music("audio/tela_de_vitoria_derrota/loop_tela_vitoria_derrota.ogg")
		, intro( (stateData.playerVictory) ? "audio/tela_de_vitoria_derrota/vitoria.ogg" : "audio/tela_de_vitoria_derrota/derrota.ogg")
		, instruction("font/SHPinscher-Regular.otf",
					END_STATE_FONT_SIZE,
					BLENDED,
					{255, 80, 80, 255},
					true) {
	Resources::ChangeMusicVolume(0);
	Resources::ChangeSoundVolume(0);

	intro.Play(1);
	Mix_HookMusicFinished(StartFinalLoop);

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

void EndState::StartLoop() {
	music.Play(0);
	Mix_HookMusicFinished(NULL);
}

void EndState::LoadAssets(void) const{
	Resources::GetImage("img/UI/end-game/prototipo-menu-vitoria.png");
	Resources::GetImage("img/UI/end-game/prototipo-menu-derrota.png");
	Resources::GetFont("font/SHPinscher-Regular.otf", 32);
	Resources::GetMusic("audio/tela_de_vitoria_derrota/vitoria.ogg");
	Resources::GetMusic("audio/tela_de_vitoria_derrota/derrota.ogg");
	Resources::GetMusic("audio/tela_de_vitoria_derrota/loop_tela_vitoria_derrota.ogg");
}
