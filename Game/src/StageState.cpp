#include "StageState.h"
#include "Camera.h"
#include "Collision.h"
#include "EndStateData.h"
#include "Enemy.h"
#include "Error.h"
#include "Tower.h"
#include "Game.h"
#include "GameResources.h"
#include "Vec2.h"

#define INCLUDE_SDL 
#define INCLUDE_SDL_IMAGE 
#include "SDL_include.h"

// Esse valores calculam o offset em relação ao canto superior esquedo da imagem daquilo que será renderizado
#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0
#define FACE_LINEAR_SIZE 30
#define TOWER_LINEAR_SIZE 120
#define TIME_BETWEEN_SPAWNS (3.)
#define STAGE_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128
#define CAM_START_X 300
#define CAM_START_Y 300
#define CAM_START_ZOOM -1.75
#define MAX_TIME_LIGHTINING_RISE 0.1
#define MAX_TIME_LIGHTINING 0.3
#define MAX_TIME_LIGHTINING_FADE 2

StageState::StageState(void)
		: State()
		, tileSet(120, 120,"map/tileset_vf.png")
		, tileMap("map/tileMap.txt", &tileSet)
		, inputManager(INPUT_MANAGER)
		, music("audio/stageState.ogg")
		, isLightning(false)
		, lightningTimer()
		, lightningColor(255, 255, 255, 0)
		, HUDcanvas()
		, menuBg("img/UI/HUD/menu.png", UIelement::BehaviorType::FIT)
		, openMenuBtn()
		, towersBtnGroup(UIgridGroup::ConstraintType::FIXED_N_COLS, 2, UIgridGroup::BehaviorOnLess::NORMAL)
		, towerBtn1()
		, towerBtn2()
		, towerBtn3()
		, towerBtn4() {
	REPORT_I_WAS_HERE;
	tileMap = TileMap(std::string("map/tileMap.txt"), &tileSet);
	
	REPORT_I_WAS_HERE;
	REPORT_I_WAS_HERE;
	music.Play(10);
	Camera::pos = Vec2(CAM_START_X, CAM_START_Y);
	Camera::ForceLogZoom(CAM_START_ZOOM);
	GameObject* waveManagerGO= new GameObject();
	waveManager= new WaveManager(tileMap, "assets/wave&enemyData.txt");
	waveManagerGO->AddComponent(waveManager);
	AddObject(waveManagerGO);

	// UI
	menuIsShowing = false;

	menuBg.SetAnchors( {1., 0.5},
					   {1., 0.5});
	menuBg.SetOffsets( {-10., (float)(-menuBg.GetSpriteHeight()/2.)},
					   {(float)menuBg.GetSpriteWidth()-(float)10., (float)(menuBg.GetSpriteHeight()/2.)});

	openMenuBtn.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/openmenu.png"));
	openMenuBtn.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/openmenu.png"));
	openMenuBtn.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/openmenu-clicked.png"));
	openMenuBtn.SetAnchors( {0., 0.},
							{0., 0.} );
	openMenuBtn.SetOffsets( {(float)-(openMenuBtn.GetStateSpriteWidth(UIbutton::State::ENABLED)), (float)10.},
							{0., openMenuBtn.GetStateSpriteHeight(UIbutton::State::ENABLED)+(float)10.} );
	openMenuBtn.SetClickCallback(this, [] (void* ptr) {
												StageState* it = static_cast<StageState*>(ptr);
												it->ToggleMenu();
											} );
	
	towersBtnGroup.SetAnchors( {0., 0.5},
							   {1., 1.} );
	towersBtnGroup.SetOffsets( {32., 0.},
							   {-27., -30.} );
	towersBtnGroup.padding = Vec2(10., 10.);

	towerBtn1.SetCenter({0.5, 0.});
	towerBtn1.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn1.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn1.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));

	towerBtn2.SetCenter({0.5, 0.});
	towerBtn2.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn2.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn2.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));

	towerBtn3.SetCenter({0.5, 0.});
	towerBtn3.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn3.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn3.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));

	towerBtn4.SetCenter({0.5, 0.});
	towerBtn4.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn4.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn4.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));

	towersBtnGroup.groupedElements.push_back(&towerBtn1);
	towersBtnGroup.groupedElements.push_back(&towerBtn2);
	towersBtnGroup.groupedElements.push_back(&towerBtn3);
	towersBtnGroup.groupedElements.push_back(&towerBtn4);
}

StageState::~StageState(void) {
	objectArray.clear();
	GameResources::Clear();
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

	//Game Over Conditions
	if(waveManager->GetLifesLeft() == 0){
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(false)));
	}else if(waveManager->Victory()){
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(true)));
	}

	if(INPUT_MANAGER.KeyPress('r')) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(true)));
	}
	if(INPUT_MANAGER.KeyPress('t')) {
		popRequested = true;
		Game::GetInstance().Push(new EndState(EndStateData(false)));
	}
	if(INPUT_MANAGER.KeyPress('q')) {
		Vec2 mousePos = Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos());
		std::cout << WHERE << "O mouse está no tile " << tileMap.GetTileMousePos(mousePos, true, 0) << ", cada layer tem " << tileMap.GetHeight()*tileMap.GetHeight() << " tiles." << END_LINE;
	}
	if(INPUT_MANAGER.MousePress(RIGHT_MOUSE_BUTTON)){
		REPORT_I_WAS_HERE;
		Vec2 mousePos = Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos());
		int position = tileMap.GetTileMousePos(mousePos, false, COLLISION_LAYER);
		GameObject *go= tileMap.GetGO(position);
		if(nullptr == go){
			std::cout<<WHERE<<"\t[WARNING] Expected GameObject" END_LINE;
		}
		else{
			go->AddComponent(new DragAndDrop(tileMap,mousePos));
			REPORT_I_WAS_HERE;
		}
	}
	if(INPUT_MANAGER.KeyPress('e')) {
		printf("Tower criado\n");
		Vec2 mousePos = Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos())-Vec2(TOWER_LINEAR_SIZE/2, TOWER_LINEAR_SIZE/2);
		Tower *newTower= new Tower(static_cast<Tower::TowerType>(rand() % TOTAL_TOWER_TYPES), mousePos, Vec2(TOWER_LINEAR_SIZE, TOWER_LINEAR_SIZE));
		AddObject(newTower);
		tileMap.InsertGO(newTower);
	}
	if(INPUT_MANAGER.KeyPress('=')) {
		Game &game = Game::GetInstance();
		game.SetMaxFramerate(game.GetMaxFramerate()+5);
	}
	if(INPUT_MANAGER.KeyPress('-')) {
		Game &game = Game::GetInstance();
		game.SetMaxFramerate( ( (int64_t)game.GetMaxFramerate() )-5);
	}
	tileMap.ShowCollisionInfo(INPUT_MANAGER.IsKeyDown('g'));
	if(INPUT_MANAGER.IsKeyDown('[')){
		Resources::ChangeMusicVolume(-STAGE_STATE_DELTA_VOLUME);
	}
	if(INPUT_MANAGER.IsKeyDown(']')){
		Resources::ChangeMusicVolume(STAGE_STATE_DELTA_VOLUME);
	}
	if(INPUT_MANAGER.IsKeyDown(',')){
		Resources::ChangeSoundVolume(-STAGE_STATE_DELTA_VOLUME);
	}
	if(INPUT_MANAGER.IsKeyDown('.')){
		Resources::ChangeSoundVolume(STAGE_STATE_DELTA_VOLUME);
	}
	if(isLightning){
		ShowLightning(dt);
	}
	else{
		isLightning = false;
		lightningTimer.Update(dt);
		if(lightningTimer.Get() > rand() % 80 + 20){
			isLightning = true;
			lightningTimer.Restart();
		}
	}

	UpdateUI(dt);

	REPORT_DEBUG("\tFrame rate: " << Game::GetInstance().GetCurrentFramerate() << "/" << Game::GetInstance().GetMaxFramerate());
}

void StageState::UpdateUI(float dt) {
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);

	openMenuBtn.angle = 180*menuIsShowing;

	HUDcanvas.Update(dt, winSize);
	menuBg.Update(dt, HUDcanvas);
	openMenuBtn.Update(dt, menuBg);
	towersBtnGroup.Update(dt, menuBg);
	towerBtn1.Update(dt, towersBtnGroup);
	towerBtn2.Update(dt, towersBtnGroup);
	towerBtn3.Update(dt, towersBtnGroup);
	towerBtn4.Update(dt, towersBtnGroup);
}

void StageState::Render(void) const {
	//renderizar o bg
	REPORT_I_WAS_HERE;
	REPORT_I_WAS_HERE;
	bool highlighted = true;
	for(unsigned int cont=0; cont < objectArray.size(); cont++) {
		if(INPUT_MANAGER.GetMousePos().IsInRect(objectArray.at(cont)->GetWorldRenderedRect())){
			highlighted = false;
			break;
		}
	}
	tileMap.Render(Vec2(0,0), false, highlighted ? Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos()) : Vec2(-1, -1));
	REPORT_I_WAS_HERE;
	State::RenderArray();
	if(isLightning){
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), lightningColor.r, lightningColor.g, lightningColor.b, lightningColor.a);
		SDL_SetRenderDrawBlendMode(Game::GetInstance().GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(Game::GetInstance().GetRenderer(), NULL);
	}

	RenderUI();
}

void StageState::RenderUI(void) const {
	// Se tivesse como ser estatico para a funcao mas uma para cada instancia, melhor ainda...
	// Mas como StageState nao teram instancias multiplas simultaneas, serve...
	static bool menuIsShowing = this->menuIsShowing;

	if(menuIsShowing) {
		menuBg.Render();
		// towersBtnGroup.Render();
		towerBtn1.Render(true);
		towerBtn2.Render(true);
		towerBtn3.Render(true);
		towerBtn4.Render(true);
	}

	openMenuBtn.Render();

	menuIsShowing = this->menuIsShowing;
}

void StageState::Pause(void) {}

void StageState::Resume(void) {
	Camera::pos = Vec2(CAM_START_X, CAM_START_Y);
	Camera::ForceLogZoom(CAM_START_ZOOM);
}

void StageState::ShowLightning(float dt){
	isLightning = true;
	lightningTimer.Update(dt);
	if(lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE){
		lightningColor.a += 256 * dt / MAX_TIME_LIGHTINING_RISE;
	}
	else if(lightningTimer.Get() >= MAX_TIME_LIGHTINING_RISE && lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING){
		lightningColor.a = 255;
	}
	else if(lightningTimer.Get() >= MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING && lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING+MAX_TIME_LIGHTINING_FADE){
		float fullTime = (MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING+MAX_TIME_LIGHTINING_FADE) - (MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING);
		lightningColor.a -= 256* ((dt / fullTime) + 1);
	}
	else{
		lightningColor.a = 0;
		isLightning = false;
		lightningTimer.Restart();
	}
}

void StageState::ToggleMenu(void) {
	menuIsShowing = !menuIsShowing;

	Rect menuBgOffsets = menuBg.GetOffsets();
	Vec2 menuBgDim = menuBg.GetSpriteDimensions();
	if(menuIsShowing) {
		menuBg.SetOffsets( {menuBgOffsets.x-menuBgDim.x, menuBgOffsets.y},
						   {menuBgOffsets.w-menuBgDim.x, menuBgOffsets.h});
	} else {
		menuBg.SetOffsets( {menuBgOffsets.x+menuBgDim.x, menuBgOffsets.y},
						   {menuBgOffsets.w+menuBgDim.x, menuBgOffsets.h});
	}

	// openMenuBtn.angle = 180*menuIsShowing;
}
