#include "StageState.h"
#include "Game.h"
#include "Error.h"
#include "Camera.h"
#include "Penguins.h"
#include "Collision.h"
#include "EndStateData.h"
#include "Face.h"

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include<SDL2/SDL_image.h>
#else
	#error "Unknown compiler"
#endif

#define STATE_RENDER_X 0//esse valores calculam o offset em relação ao canto superior esquedo da imagem daquilo que será renderizado
#define STATE_RENDER_Y 0
StageState::StageState(void)
			:State(), bg("img/ocean.jpg"),
				tileSet(30, 30,"img/tileset-basico.jpg"),
				inputManager(InputManager::GetInstance()),
				music("audio/stageState.ogg") {
	REPORT_I_WAS_HERE;
	tileMap= new TileMap(std::string("map/tileMap.txt"), &tileSet, "map/CollisionTileMap.txt");
	REPORT_I_WAS_HERE;
	objectArray.emplace_back(std::unique_ptr<Penguins>( new Penguins (704, 640) ) );
	music.Play(10);
}

StageState::~StageState(void) {
	objectArray.clear();
	delete tileMap;
}

//void StageState::Update(float dt)
void StageState::Update(float dt) {
	REPORT_I_WAS_HERE;
//	Input();
	if(inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested= true;
	}
	if(inputManager.QuitRequested()) {
		quitRequested= true;
	}
	UpdateArray(dt);
	for(unsigned int count1=0; count1 < objectArray.size()-1; count1++) {
		for(unsigned int count2= count1+1; count2 < objectArray.size(); count2++) {
			if(Collision::IsColliding(objectArray[count1]->box, objectArray[count2]->box, objectArray[count1]->rotation, objectArray[count2]->rotation) ) {
				objectArray[count1]->NotifyCollision(*objectArray[count2]);
				objectArray[count2]->NotifyCollision(*objectArray[count1]);
			}
		}
	}
	Camera::Update(dt);
	REPORT_I_WAS_HERE;
	if(nullptr == Penguins::player) {
		popRequested= true;
		Game::GetInstance().Push(new EndState(EndStateData(false)));
	}
	if(InputManager::GetInstance().KeyPress('r')) {
		popRequested= true;
		Game::GetInstance().Push(new EndState(EndStateData(true)));
	}
	if(InputManager::GetInstance().KeyPress('t')) {
		popRequested= true;
		Game::GetInstance().Push(new EndState(EndStateData(false)));
	}
	if(InputManager::GetInstance().KeyPress('q')){
		Vec2 mousePos= InputManager::GetInstance().GetMousePos();
		std::cout << WHERE << "O mouse está no tile " << tileMap->GetTileMousePos(mousePos, true, 0) << ", cada layer tem " << tileMap->GetHeight()*tileMap->GetHeight() << " tiles." << std::endl;
	}
	if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)){
		REPORT_I_WAS_HERE;
		Vec2 mousePos= InputManager::GetInstance().GetMousePos()+Camera::pos-Vec2(15, 15);//metade to tamanho da Face passado abaixo
		AddObject(new Face(mousePos.x, mousePos.y, Vec2(30, 30), tileMap) );
	}
	if(InputManager::GetInstance().KeyPress('e')){
		printf("Face criado\n");
		AddObject(new Face(0, 0, Vec2(64, 64), tileMap));
	}
	if(InputManager::GetInstance().KeyPress('=')){
		Game &game= Game::GetInstance();
		game.SetMaxFramerate(game.GetMaxFramerate()+5);
	}
	if(InputManager::GetInstance().KeyPress('-')){
		Game &game= Game::GetInstance();
		game.SetMaxFramerate( ( (int64_t)game.GetMaxFramerate() )-5);
	}
	REPORT_DEBUG("\tFrame rate: " << Game::GetInstance().GetCurrentFramerate() << "/" << Game::GetInstance().GetMaxFramerate());
}

void StageState::Render(void) const {
	//renderizar o bg
	REPORT_I_WAS_HERE;
	bg.Render(STATE_RENDER_X, STATE_RENDER_Y);
	REPORT_I_WAS_HERE;
	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
//	tileMap->Render(Camera::pos.x, Camera::pos.y);
	REPORT_I_WAS_HERE;
	State::RenderArray();
	tileMap->RenderLayer(1, Camera::pos.x, Camera::pos.y);
//	goTileMap.Render();
}

void StageState::Pause(void) {}

void StageState::Resume(void) {}



