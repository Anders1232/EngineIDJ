#include "EndState.h"

EndState::EndState(EndStateData stateData)
		: bg((stateData.playerVictory)?"img/win.jpg":"img/lose.jpg"),
			music((stateData.playerVictory)?"audio/endStateWin.ogg": "audio/endStateLose.ogg"),
			instruction( "font/Call me maybe.ttf",
						END_STATE_FONT_SIZE,
						BLENDED,
<<<<<<< HEAD
						{255, 255, 255, 255}
						) {
=======
				 		{255, 255, 255, 255},
						 true
			   		 ) {
>>>>>>> e5875c5e599648c41a87e8ace402ea4999f3fa08
	music.Play(0);
	instruction.SetText("Press Esc to go to menu or Space to play again!");
	instruction.SetTimeShown(0.6);
	instruction.SetStrobeFrequency(1.0);

	bg.Render(0, 0);
	Vec2 pos= Game::GetInstance().GetWindowDimensions();
	if(stateData.playerVictory) {
		instruction.SetPos(0, pos.y*0.005, true);
	}
	else {
		instruction.SetPos(0, pos.y-instruction.GetSize().y, true);
	}
}

<<<<<<< HEAD
void EndState::Update(float dt){
	if(InputManager::GetInstance().QuitRequested()){
=======
void EndState::Update(float dt) {
	instruction.Update(dt);
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.QuitRequested()) {
>>>>>>> e5875c5e599648c41a87e8ace402ea4999f3fa08
		quitRequested= true;
	}
	if(ActionManager::EscapeAction()){
		popRequested=true;
	}
	if(ActionManager::StartAction()){
		popRequested= true;
		Game::GetInstance().Push(new StageState());
	}
}

void EndState::Render() const {
	bg.Render(0, 0);
	instruction.Render();
}

void EndState::Pause() {}

void EndState::Resume() {}

