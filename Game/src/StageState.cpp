#include "StageState.h"

#include "Camera.h"
#include "Collision.h"
#include "EndStateData.h"
#include "Enemy.h"
#include "Error.h"
#include "Face.h"
#include "Game.h"

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include "TargetConditionals.h"
	//mac
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#else
	#error "Unknown compiler"
#endif

// Esse valores calculam o offset em relação ao canto superior esquedo da imagem daquilo que será renderizado
#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0
#define FACE_LINEAR_SIZE 30
#define TIME_BETWEEN_SPAWNS (3.)
#define STAGE_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128
#define CAM_START_X 300
#define CAM_START_Y 300
#define CAM_START_ZOOM 0.3

StageState::StageState(void)
		: State()
		, bg("img/ocean.jpg")
		, tileSet(120, 120,"img/map/tileset_v2.png")
		, inputManager(InputManager::GetInstance())
		, music("audio/stageState.ogg")
		, spawnTimer() {
	REPORT_I_WAS_HERE;
	tileMap = new TileMap(std::string("map/tileMap.txt"), &tileSet);
	REPORT_I_WAS_HERE;
	spawnGroups = tileMap->GetSpawnPositions();
	REPORT_I_WAS_HERE;
	music.Play(10);
	Camera::pos = Vec2(CAM_START_X, CAM_START_Y);
	Camera::ForceZoom(CAM_START_ZOOM);
}

StageState::~StageState(void) {
	objectArray.clear();
	delete tileMap;
	delete spawnGroups;
}

void StageState::Update(float dt) {
	REPORT_I_WAS_HERE;
	if(ActionManager::EscapeAction()) {
		popRequested = true;
	}
	if(inputManager.QuitRequested()) {
		quitRequested = true;
	}
	REPORT_I_WAS_HERE;
	
	UpdateArray(dt);
	REPORT_I_WAS_HERE;
	if(!objectArray.empty()){
		for(unsigned int count1 = 0; count1 < objectArray.size()-1; count1++) {
			for(unsigned int count2 = count1+1; count2 < objectArray.size(); count2++) {
				if(Collision::IsColliding(objectArray[count1]->box, objectArray[count2]->box, objectArray[count1]->rotation, objectArray[count2]->rotation) ) {
					objectArray[count1]->NotifyCollision(*objectArray[count2]);
					objectArray[count2]->NotifyCollision(*objectArray[count1]);
					REPORT_I_WAS_HERE;
				}
			}
		}
	}
	REPORT_I_WAS_HERE;
	
	Camera::Update(dt);
	REPORT_I_WAS_HERE;
	spawnTimer.Update(dt);
	if(TIME_BETWEEN_SPAWNS < spawnTimer.Get()) {
		int selectedSpawnGroup = rand() % spawnGroups->size();
		int selectedSpawnPosition = rand() % ( (*spawnGroups)[selectedSpawnGroup] ).size();
		SpawnEnemy( (*spawnGroups)[selectedSpawnGroup][selectedSpawnPosition] );
		spawnTimer.Restart();
	}

	if(InputManager::GetInstance().KeyPress('r')) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(true)));
	}

	if(InputManager::GetInstance().KeyPress('t')) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(false)));
	}

	if(InputManager::GetInstance().KeyPress('q')) {
		Vec2 mousePos = Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos());
		std::cout << WHERE << "O mouse está no tile " << tileMap->GetTileMousePos(mousePos, true, 0) << ", cada layer tem " << tileMap->GetHeight()*tileMap->GetHeight() << " tiles." << std::endl;
	}

	if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
		REPORT_I_WAS_HERE;
		Vec2 mousePos = Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos())-Vec2(FACE_LINEAR_SIZE/2, FACE_LINEAR_SIZE/2);//metade to tamanho da Face passado abaixo
		AddObject( new Face(mousePos.x, mousePos.y, Vec2(FACE_LINEAR_SIZE, FACE_LINEAR_SIZE), tileMap) );
	}

	if(InputManager::GetInstance().KeyPress('e')) {
		printf("Face criado\n");
		AddObject(new Face(0, 0, Vec2(64, 64), tileMap));
	}

	if(InputManager::GetInstance().KeyPress('=')) {
		Game &game = Game::GetInstance();
		game.SetMaxFramerate(game.GetMaxFramerate()+5);
	}

	if(InputManager::GetInstance().KeyPress('-')) {
		Game &game = Game::GetInstance();
		game.SetMaxFramerate( ( (int64_t)game.GetMaxFramerate() )-5);
	}

	tileMap->ShowCollisionInfo(InputManager::GetInstance().IsKeyDown('g'));

	if(InputManager::GetInstance().IsKeyDown('[')){
		Resources::ChangeMusicVolume(-STAGE_STATE_DELTA_VOLUME);
	}

	if(InputManager::GetInstance().IsKeyDown(']')){
		Resources::ChangeMusicVolume(STAGE_STATE_DELTA_VOLUME);
	}

	if(InputManager::GetInstance().IsKeyDown(',')){
		Resources::ChangeSoundVolume(-STAGE_STATE_DELTA_VOLUME);
	}

	if(InputManager::GetInstance().IsKeyDown('.')){
		Resources::ChangeSoundVolume(STAGE_STATE_DELTA_VOLUME);
	}

	REPORT_DEBUG("\tFrame rate: " << Game::GetInstance().GetCurrentFramerate() << "/" << Game::GetInstance().GetMaxFramerate());
}

void StageState::Render(void) const {
	//renderizar o bg
	REPORT_I_WAS_HERE;
	bg.Render(Rect(STATE_RENDER_X, STATE_RENDER_Y, 0, 0), 0, false);
	REPORT_I_WAS_HERE;
	bool highlighted = true;
	for(unsigned int cont=0; cont < objectArray.size(); cont++) {
		if(InputManager::GetInstance().GetMousePos().IsInRect(objectArray.at(cont)->GetWorldRenderedRect())){
			highlighted = false;
			break;
		}
	}
	tileMap->Render(Vec2(0,0), false, highlighted ?  Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos()) : Vec2(-1, -1));
	REPORT_I_WAS_HERE;
	State::RenderArray();
}

void StageState::Pause(void) {}

void StageState::Resume(void) {}

void StageState::SpawnEnemy(int tileMapPosition) {
	Vec2 tileSize = tileMap->GetTileSize();
	Vec2 spawnPosition;
	spawnPosition.x = (tileMapPosition % tileMap->GetWidth() ) * tileSize.x;
	spawnPosition.y = (tileMapPosition / tileMap->GetWidth() ) * tileSize.y;
	objectArray.push_back(unique_ptr<GameObject>( new Enemy(spawnPosition, 1.0) ));
}
