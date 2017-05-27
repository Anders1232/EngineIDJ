#include "EndState.h"

EndState::EndState(EndStateData stateData):
	bg((stateData.playerVictory)?"img/win.jpg":"img/lose.jpg"),
	music((stateData.playerVictory)?"audio/endStateWin.ogg": "audio/endStateLose.ogg"),
	instruction
	(
		"font/Call me maybe.ttf",
		END_STATE_FONT_SIZE,
		BLENDED,
		{255, 255, 255, 255}
	)
{
	music.Play(0);
	instruction.SetText("Press Esc to go to menu or Space to play again!");

	bg.Render(0, 0);
	Vec2 pos= Game::GetInstance().GetWindowDimensions();
	if(stateData.playerVictory)
	{
		instruction.SetPos(0, pos.y*0.005, true);
	}
	else
	{
		instruction.SetPos(0, pos.y-instruction.GetSize().y, true);
	}
}

void EndState::Update(float dt)
{
	InputManager &inputManager= InputManager::GetInstance();
	if(inputManager.QuitRequested())
	{
		quitRequested= true;
	}
	if(inputManager.EscapeAction())
	{
		popRequested=true;
	}
	if(inputManager.StartAction())
	{
		popRequested= true;
		Game::GetInstance().Push(new StageState());
	}
}
void EndState::Render() const
{
	bg.Render(0, 0);
	instruction.Render();
}
void EndState::Pause()
{}
void EndState::Resume()
{}

