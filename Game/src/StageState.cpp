#include "StageState.h"
#include "AIArt.h"
#include "AIEngineer.h"
#include "AIMedic.h"
#include "AIQuimic.h"
#include "Camera.h"
#include "Collision.h"
#include "EndStateData.h"
#include "Enemy.h"
#include "Error.h"
#include "Game.h"
#include "GameResources.h"
#include "Obstacle.h"
#include "Vec2.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

// Esse valores calculam o offset em relação ao canto superior esquedo da imagem daquilo que será renderizado
#define STATE_RENDER_X 0
#define STATE_RENDER_Y 0
#define FACE_LINEAR_SIZE 30
#define TIME_BETWEEN_SPAWNS (8.)
#define TOWER_LINEAR_SIZE 120
#define STAGE_STATE_DELTA_VOLUME (1) //11*11 = 121 ~128
#define CAM_START_X 300
#define CAM_START_Y 300
#define CAM_START_ZOOM -1.75
#define MAX_TIME_LIGHTINING_RISE 0.1 // s
#define MAX_TIME_LIGHTINING 0.3 // s
#define MAX_TIME_LIGHTINING_FADE 2 // s
#define LIGHTINING_MIN_INTERVAL 30 // s
#define LIGHTINING_MAX_INTERVAL 60 // s
#define TREE_1_TILESET_INDEX 70
#define TREE_2_TILESET_INDEX 71
#define TREE_3_TILESET_INDEX 72
#define POLE_TILESET_INDEX 73
#define BENCH_TILESET_INDEX 76

#define TOWER_INFO_TXT_COLOR {199,159,224,255} // Purple-ish white

StageState::StageState(void)
		: State()
		, tileSet(120, 120,"map/tileset_vf.png")
		, tileMap("map/tileMap.txt", &tileSet)
		, inputManager(INPUT_MANAGER)
        , music("audio/trilha_sonora/loop_1.ogg")
		, isLightning(false)
		, isThundering(false)
		, lightningTimer()
		, lightningColor(255, 255, 255, 0)
		, nightSound("audio/Ambiente/Barulho_noite.wav")
		, thunderSound("audio/Ambiente/Trovao.wav")
		, frameRateCounter(0)
		, HUDcanvas()
		, menuBg("img/UI/HUD/menu.png", UIelement::BehaviorType::FIT)
		, openMenuBtn()
		, towerInfoGroup()
		, towerName("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, TOWER_INFO_TXT_COLOR, TOWERNAME_DEFAULT_TEXT)
		, towerCost("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, TOWER_INFO_TXT_COLOR, TOWERCOST_DEFAULT_TEXT)
		, towerDamage("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, TOWER_INFO_TXT_COLOR, TOWERDAMAGE_DEFAULT_TEXT)
		, towerDamageType("font/SHPinscher-Regular.otf", 95, UItext::TextStyle::BLENDED, TOWER_INFO_TXT_COLOR, TOWERDAMGETYPE_DEFAULT_TEXT)
		, towersBtnGroup(UIgridGroup::ConstraintType::FIXED_N_COLS, 2, UIgridGroup::BehaviorOnLess::NORMAL)
		, towerBtn1()
		, towerBtn2()
		, towerBtn3()
		, towerBtn4()
		, health()
		, healthIcon("img/UI/HUD/vida00.png", UIelement::BehaviorType::FILL)
		, healthbarBg("img/UI/HUD/hudvida.png")
		, healthbarBar("img/UI/HUD/hudvida.png")
		, wave()
		, waveIcon("img/UI/HUD/inimigo00.png", UIelement::BehaviorType::FILL)
		, wavebarBg("img/UI/HUD/hudvida.png")
		, wavebarBar("img/UI/HUD/hudvida.png") {

	GameResources::SetTileMap(&tileMap);
	REPORT_I_WAS_HERE;
	music.Play(10);
	Camera::pos = Vec2(CAM_START_X, CAM_START_Y);
	Camera::ForceLogZoom(CAM_START_ZOOM);
	GameObject* waveManagerGO= new GameObject();
	waveManager= new WaveManager(tileMap, "assets/wave&enemyData.txt");
	waveManagerGO->AddComponent(waveManager);
	AddObject(waveManagerGO);
	
	tileMap.ObserveMapChanges(this);
	lightningInterval = rand() % (LIGHTINING_MAX_INTERVAL - LIGHTINING_MIN_INTERVAL) + LIGHTINING_MIN_INTERVAL;
	REPORT_DEBUG(" Proximo relampago sera em " << lightningInterval << " segundos.");
	InitializeObstacles();
	nightSound.Play(-1);

	SetupUI();
}

void StageState::SetupUI() {
	Vec2 winSize = Game::GetInstance().GetWindowDimensions();

	// Side Menu
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
	
	towerInfoGroup.SetAnchors( {0.165, 0.05},
						  {0.86, 0.425});
	towerInfoGroup.SetOffsets( {5., 5.},
						  {-5., -5.});

	towerInfoGroup.groupedElements.push_back(&towerName);
	towerInfoGroup.groupedElements.push_back(&towerCost);
	towerInfoGroup.groupedElements.push_back(&towerDamage);
	towerInfoGroup.groupedElements.push_back(&towerDamageType);
	
	towersBtnGroup.SetAnchors( {0., 0.485},
							   {1., 1.} );
	towersBtnGroup.SetOffsets( {32., 0.},
							   {-27., -30.} );
	towersBtnGroup.padding = Vec2(10., 10.);

	towerBtn1.SetCenter({0.5, 0.});
	towerBtn1.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn1.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn1.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));
	towerBtn1.SetCallback(UIbutton::State::HIGHLIGHTED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData("Normal (Art)", "$1", "10 HP", "Projetil (3/s)");
																} );
	towerBtn1.SetCallback(UIbutton::State::ENABLED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData();
																} );
	towerBtn1.SetClickCallback(this, [] (void* ptr) {
											StageState* it = static_cast<StageState*>(ptr);
											it->CreateTower(Tower::TowerType::ARTS);
										} );

	towerBtn2.SetCenter({0.5, 0.});
	towerBtn2.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn2.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn2.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));
	towerBtn2.SetCallback(UIbutton::State::HIGHLIGHTED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData("Tentaculo (Soc)", "$10", "10 segundos", "Stun");
																} );
	towerBtn2.SetCallback(UIbutton::State::ENABLED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData();
																} );
	towerBtn2.SetClickCallback(this, [] (void* ptr) {
											StageState* it = static_cast<StageState*>(ptr);
											it->CreateTower(Tower::TowerType::SOCIOLOGY);
										} );

	towerBtn3.SetCenter({0.5, 0.});
	towerBtn3.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn3.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn3.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));
	towerBtn3.SetCallback(UIbutton::State::HIGHLIGHTED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData("Eletrico (Eng)", "$100", "20 HP/segundo", "Proximidade");
																} );
	towerBtn3.SetCallback(UIbutton::State::ENABLED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData();
																} );
	towerBtn3.SetClickCallback(this, [] (void* ptr) {
											StageState* it = static_cast<StageState*>(ptr);
											it->CreateTower(Tower::TowerType::ENGINEERING);
										} );

	towerBtn4.SetCenter({0.5, 0.});
	towerBtn4.SetStateSprite(UIbutton::State::ENABLED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn4.SetStateSprite(UIbutton::State::HIGHLIGHTED, new Sprite("img/UI/HUD/botaotorre.png"));
	towerBtn4.SetStateSprite(UIbutton::State::PRESSED, new Sprite("img/UI/HUD/botaotorre-clicked.png"));
	towerBtn4.SetCallback(UIbutton::State::HIGHLIGHTED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData("Nuke (Med)", "$9999", "+Inf HP", "Area");
																} );
	towerBtn4.SetCallback(UIbutton::State::ENABLED, this, [] (void* ptr) {
																	StageState* it = static_cast<StageState*>(ptr);
																	it->SetTowerInfoData();
																} );
	towerBtn4.SetClickCallback(this, [] (void* ptr) {
											StageState* it = static_cast<StageState*>(ptr);
											it->CreateTower(Tower::TowerType::MEDICINE);
										} );

	towersBtnGroup.groupedElements.push_back(&towerBtn1);
	towersBtnGroup.groupedElements.push_back(&towerBtn2);
	towersBtnGroup.groupedElements.push_back(&towerBtn3);
	towersBtnGroup.groupedElements.push_back(&towerBtn4);

	// Game Info
	health.SetAnchors( {(float)(30.+healthIcon.GetSpriteWidth())/(2*winSize.x), (float)10./winSize.y},
					   {(float)300./winSize.x, (float)35./winSize.y} );
	health.SetOffsets( {(float)(30.+healthIcon.GetSpriteWidth())/2, 0.},
					   {120., 25.} );

	healthIcon.SetCenter( {.725, 0.5} );
	healthIcon.SetAnchors( {0., 0.1},
						   {0., 0.9} );

	healthbarBg.SetAnchors( {0., 0.3},
							 {1., 0.7} );
	healthbarBg.SetSpriteColorMultiplier({0, 0, 0, 255});
	
	Rect healthBox = health.ComputeBox(health.ComputeBoundingbox( {0., 0., winSize.x, winSize.y} ));
	healthbarBar.SetAnchors( {(float)0., (float)0.3+2/healthBox.h},
							 {(float)1., (float)0.7-2/healthBox.h} );
	healthbarBar.SetOffsets( {(float)2., 0.},
							 {(float)-2., 0.} );
	healthbarBar.SetSpriteColorMultiplier({180, 225, 149, 255});


	wave.SetAnchors( {(float)(30.+healthIcon.GetSpriteWidth())/(2*winSize.x), (float)35./winSize.y},
					 {(float)150./winSize.x, (float)60./winSize.y} );
	wave.SetOffsets( {(float)(30.+waveIcon.GetSpriteWidth())/2, 25.},
					 {120., 50.} );

	waveIcon.SetCenter( {.725, 0.5} );
	waveIcon.SetAnchors( {0., 0.1},
						 {0., 0.9} );

	wavebarBg.SetAnchors( {0., 0.3},
						  {1., 0.7} );
	wavebarBg.SetSpriteColorMultiplier({0, 0, 0, 255});
	
	Rect waveBox = wave.ComputeBox(wave.ComputeBoundingbox( {0., 0., winSize.x, winSize.y} ));
	wavebarBar.SetAnchors( {(float)0., (float)0.3+2/waveBox.h},
						   {(float)1., (float)0.7-2/waveBox.h} );
	wavebarBar.SetOffsets( {(float)2., 0.},
						   {(float)-2., 0.} );
	wavebarBar.SetSpriteColorMultiplier({154, 148, 104, 255});

}

StageState::~StageState(void) {
	std::cout<<WHERE<<"\tGameResources path hit rate: " << GameResources::GetPathHitRate()<<END_LINE;
	objectArray.clear();
	obstacleArray.clear();
	tileMap.RemoveObserver(this);
	GameResources::Clear();
	TEMP_REPORT_I_WAS_HERE;
	nightSound.Stop();
}

void StageState::Update(float dt){
	REPORT_I_WAS_HERE;
	if(ActionManager::EscapeAction()) {
		popRequested = true;
	}
	if(inputManager.QuitRequested()) {
		quitRequested = true;
	}
	//fazendo o prórpio loop de atualização ao invés do UpdateArray pois estamos fazendo checagens adicionais
	for(unsigned int cont = 0; cont < objectArray.size(); cont++) {
		objectArray.at(cont)->Update(dt);
		if(objectArray.at(cont)->IsDead()) {
			int64_t objOnTileMap= tileMap.Have(objectArray[cont].get());
			if(0 <= objOnTileMap){
				tileMap.RemoveGO(objOnTileMap);
			}
			objectArray.erase(objectArray.begin()+cont);
			cont--;
		}
	}

	if(!objectArray.empty()){
		for(uint count1 = 0; count1 < objectArray.size()-1; count1++) {
			for(uint count2 = count1+1; count2 < objectArray.size(); count2++) {
				if(Collision::IsColliding(objectArray[count1]->box, objectArray[count2]->box, objectArray[count1]->rotation, objectArray[count2]->rotation) ) {
					objectArray[count1]->NotifyCollision(*objectArray[count2]);
					objectArray[count2]->NotifyCollision(*objectArray[count1]);
				}
			}
		}
	}

	Camera::Update(dt);

	// Game Over Conditions
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
		std::cout << WHERE << "O mouse está no tile " << tileMap.GetCoordTilePos(mousePos, true, 0) << ", cada layer tem " << tileMap.GetHeight()*tileMap.GetHeight() << " tiles." << END_LINE;

	}
	if(INPUT_MANAGER.MousePress(RIGHT_MOUSE_BUTTON)) {
		Vec2 mousePos = Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos());
		int position = tileMap.GetCoordTilePos(mousePos, false, COLLISION_LAYER);
		GameObject *go = tileMap.GetGO(position);
		if(nullptr != go) {
			go->AddComponent(new DragAndDrop(tileMap, mousePos, *go));
			REPORT_I_WAS_HERE;
		}
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
		if(!isThundering){
			thunderSound.Play(1);
			isThundering = true;
		}
		ShowLightning(dt);
	}
	else{
		isLightning = false;
		isThundering = false;
		lightningTimer.Update(dt);
		if(lightningTimer.Get() > lightningInterval){
			isLightning = true;
			lightningTimer.Restart();
			lightningInterval = rand() % (LIGHTINING_MAX_INTERVAL - LIGHTINING_MIN_INTERVAL) + LIGHTINING_MIN_INTERVAL;
			REPORT_DEBUG(" Proximo relampago sera em " << lightningInterval << " segundos.");
		}
	}

	UpdateUI(dt);

	REPORT_DEBUG("\tFrame rate: " << Game::GetInstance().GetCurrentFramerate() << "/" << Game::GetInstance().GetMaxFramerate());
	//depois isolar essa lógica num componente.
	frameRateTimer.Update(dt);
	frameRateCounter++;
	if(1. <= frameRateTimer.Get()){
		std::cout<<WHERE<<"\t Frame Rate: " << (float)frameRateCounter/frameRateTimer.Get()<<"/"<<Game::GetInstance().GetMaxFramerate()<< END_LINE;
		frameRateCounter=0;
		frameRateTimer.Restart();
	}
}

void StageState::UpdateUI(float dt) {
	Rect winSize(0., 0., Game::GetInstance().GetWindowDimensions().x, Game::GetInstance().GetWindowDimensions().y);

	openMenuBtn.angle = 180*menuIsShowing;

	HUDcanvas.Update(dt, winSize);

	menuBg.Update(dt, HUDcanvas);

	openMenuBtn.Update(dt, menuBg);

	towerInfoGroup.Update(dt, menuBg);
	towerName.Update(dt, towerInfoGroup);
	towerCost.Update(dt, towerInfoGroup);
	towerDamage.Update(dt, towerInfoGroup);
	towerDamageType.Update(dt, towerInfoGroup);

	towersBtnGroup.Update(dt, menuBg);
	towerBtn1.Update(dt, towersBtnGroup);
	towerBtn2.Update(dt, towersBtnGroup);
	towerBtn3.Update(dt, towersBtnGroup);
	towerBtn4.Update(dt, towersBtnGroup);


	health.Update(dt, HUDcanvas);
	healthIcon.Update(dt, health);
	healthbarBg.Update(dt, health);
	healthbarBar.Update(dt, health);

	wave.Update(dt, HUDcanvas);
	waveIcon.Update(dt, wave);
	wavebarBg.Update(dt, wave);
	wavebarBar.Update(dt, wave);
}

void StageState::Render(void) const {
	REPORT_I_WAS_HERE;
	bool highlighted = true;
	for(unsigned int cont=0; cont < objectArray.size(); cont++) {
		if(INPUT_MANAGER.GetMousePos().IsInRect(objectArray.at(cont)->GetWorldRenderedRect())){
			highlighted = false;
			break;
		}
	}
	tileMap.Render(Vec2(0,0), false, highlighted ? Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos()) : Vec2(-1, -1));
	RenderObstacleArray();
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
		// towerInfoGroup.Render(true);
		towerName.Render();
		towerCost.Render();
		towerDamage.Render();
		towerDamageType.Render();
		// towersBtnGroup.Render(true);
		towerBtn1.Render();
		towerBtn2.Render();
		towerBtn3.Render();
		towerBtn4.Render();
	}
	openMenuBtn.Render();

	// health.Render(true);
	healthbarBg.Render();
	healthbarBar.Render();
	healthIcon.Render();

	// wave.Render(true);
	wavebarBg.Render();
	wavebarBar.Render();
	waveIcon.Render();

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
	float newAlpha;
	if(lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE){
		newAlpha = lightningColor.a + 256 * dt / MAX_TIME_LIGHTINING_RISE;
	}
	else if(lightningTimer.Get() >= MAX_TIME_LIGHTINING_RISE && lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING){
		newAlpha = 255;
	}
	else if(lightningTimer.Get() >= MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING && lightningTimer.Get() < MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING+MAX_TIME_LIGHTINING_FADE){
		float fullTime = (MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING+MAX_TIME_LIGHTINING_FADE) - (MAX_TIME_LIGHTINING_RISE+MAX_TIME_LIGHTINING);
		newAlpha = lightningColor.a - 256* (dt / fullTime);
	}
	else{
		newAlpha = 0;
		isLightning = false;
		lightningTimer.Restart();
	}
	lightningColor.a = newAlpha > 255 ? 255 : newAlpha < 0 ? 0 : newAlpha;
}

void StageState::NotifyTileMapChanged(int tilePosition){
	GameResources::NotifyTileMapChanged(tilePosition);
}

void StageState::AddObstacle(Obstacle *obstacle) {
	obstacleArray.push_back(std::unique_ptr<Obstacle>(obstacle));
}

void StageState::RenderObstacleArray(void) const {
	REPORT_I_WAS_HERE;
#ifdef RENDER_FOWARD
	for(unsigned int cont = 0; cont < obstacleArray.size(); cont++) {
#else
	for(int64_t cont = ((int64_t)obstacleArray.size()) -1; 0 <= cont ; cont--) {
#endif
		obstacleArray[cont]->Render();
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
}

void StageState::SetTowerInfoData(string name, string cost, string damage, string damageType) {
	towerName.SetText(name);
	towerCost.SetText(cost);
	towerDamage.SetText(damage);
	towerDamageType.SetText(damageType);
}

void StageState::CreateTower(Tower::TowerType towerType) {
	ToggleMenu();

	Vec2 mousePos = Camera::ScreenToWorld(INPUT_MANAGER.GetMousePos())-Vec2(TOWER_LINEAR_SIZE/2, TOWER_LINEAR_SIZE/2);
	Tower *newTower = new Tower(towerType, mousePos, Vec2(TOWER_LINEAR_SIZE, TOWER_LINEAR_SIZE), TOWER_BASE_HP);
	newTower->AddComponent(new DragAndDrop(tileMap, mousePos, *newTower, false, false));
	AddObject(newTower);
}

void StageState::SetUILife(float lifePercent) {
	lifePercent = (lifePercent < 0) ? 0 : ((lifePercent > 1) ? 1 : lifePercent);
	Rect oldAnchor = healthbarBar.GetAnchors();
	healthbarBar.SetAnchors( {oldAnchor.x, oldAnchor.y},
							 {lifePercent, oldAnchor.h} );
}

void StageState::SetUIWaveProgress(float waveProgressPercent) {
	waveProgressPercent = (waveProgressPercent < 0) ? 0 : ((waveProgressPercent > 1) ? 1 : waveProgressPercent);
	Rect oldAnchor = wavebarBar.GetAnchors();
	wavebarBar.SetAnchors( {oldAnchor.x, oldAnchor.y},
							 {waveProgressPercent, oldAnchor.h} );
}

void StageState::InitializeObstacles(void){
	/*
	70 a 72 3 tipos de arvores
	73 poste
	76 banco
	*/
	int index;
	int mapWidth= tileMap.GetWidth();
	Vec2 tileSize= tileMap.GetTileSize();
	int tileWidth= tileSize.x;
	int tileHeight= tileSize.y;
	std::array<vector<vector<int>>*, 3> treeTiles;
	treeTiles[0] = tileMap.GetTileGroups(TREE_1_TILESET_INDEX);
	treeTiles[1] = tileMap.GetTileGroups(TREE_2_TILESET_INDEX);
	treeTiles[2] = tileMap.GetTileGroups(TREE_3_TILESET_INDEX);
	vector<vector<int>>* poleTiles = tileMap.GetTileGroups(POLE_TILESET_INDEX);
	vector<vector<int>>* benchTiles = tileMap.GetTileGroups(BENCH_TILESET_INDEX);
	for(uint count = 0; count < treeTiles.size(); count++){
		vector<vector<int>> &treeGroup= *(treeTiles[count]);
		for(uint i = 0; i < treeGroup.size(); i++){
			vector<int> &treeTilesVector= treeGroup[i];
			for(uint j = 0; j < treeTilesVector.size(); j++){
				Obstacle* tree= nullptr;
				index = treeTilesVector[j];
				if(treeTilesVector.size() <= (j+1) ){
					//checar as alternativas gerará um seg fault
					tree = new Obstacle("./img/obstacle/arvore1.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
				}
				else{
					auto baixo= std::find(treeTilesVector.begin(), treeTilesVector.end(),treeTilesVector[j]+tileMap.GetWidth());
					if(baixo != treeTilesVector.end()){
						//tem um tile em baixo
						if(treeTilesVector[j+1] == (index+1) ){
							//tem uma linha e uma coluna a partir do tile sendo processado
							bool isSqare=false;
							if( (baixo+1) != treeTilesVector.end())
							{
								if(*(baixo+1) == (*baixo)+1){
									//é um quadrado
									isSqare = true;
									tree = new Obstacle("./img/obstacle/arvore4.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
									treeTilesVector.erase(baixo+1);
									treeTilesVector.erase(baixo);
									treeTilesVector.erase(treeTilesVector.begin()+(j+1) );
								}
							}
							if(!isSqare){
								//é uma coluna
								tree = new Obstacle("./img/obstacle/arvore3.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
								treeTilesVector.erase(baixo);
							}
						}
					}
					if(nullptr == tree){
						if(treeTilesVector[j+1] == index+1){
							//é uma linha
							tree = new Obstacle("./img/obstacle/arvore2.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
							treeTilesVector.erase(treeTilesVector.begin()+(j+1) );
						}
						else{
							//é apenas um tile
							tree = new Obstacle("./img/obstacle/arvore1.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
						}
					}
				}
				if(nullptr != tree){
					tileMap.InsertGO(tree, false);
					AddObstacle(tree);
				}
				else{
					REPORT_DEBUG2(1, "\t[WARNING] Couldn't place a tree on tileMap!");
				}
			}
		}
	}
	delete treeTiles[0];
	delete treeTiles[1];
	delete treeTiles[2];
	for(uint i = 0; i < poleTiles->size(); i++){
		for(uint j = 0; j < poleTiles->at(i).size(); j++){
			index = poleTiles->at(i)[j];
			Obstacle* pole = new Obstacle("./img/obstacle/posteLuz.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
			tileMap.InsertGO(pole, false);
			AddObstacle(pole);
			pole->SpriteScaleY(2.2);
			pole->box.y= pole->box.y - 1.2*tileMap.GetTileSize().y;
			pole->box.h= 2.2*tileMap.GetTileSize().y;
			pole->box.x-= pole->box.w/4;
		}
	}
	delete poleTiles;
	for(uint i = 0; i < benchTiles->size(); i++){
		for(uint j = 0; j < benchTiles->at(i).size(); j++){
			index = benchTiles->at(i)[j];
			Obstacle* bench = new Obstacle("./img/obstacle/banco_h.png", Vec2(index%mapWidth*tileWidth, index/mapWidth*tileHeight));
			tileMap.InsertGO(bench, false);
			AddObstacle(bench);
		}
	}
	delete benchTiles;
}

GameObject* StageState::FindNearestGO(Vec2 origin, std::string targetType, float range){
	GameObject* closerObj = nullptr;
	double closerObjDistance = std::numeric_limits<double>::max();
	for(unsigned int i = 0; i < objectArray.size(); i ++){
		std::unique_ptr<GameObject> &gameObjectInAnalisis= objectArray[i];
		if(nullptr != gameObjectInAnalisis){
			if(gameObjectInAnalisis->Is(targetType)){
				double distance = origin.VecDistance(gameObjectInAnalisis->box.Center()).Magnitude();
				if(distance < closerObjDistance && distance <= range){
					closerObjDistance = distance;
					closerObj = gameObjectInAnalisis.get();
				}
			}
		}
	}
	return(closerObj);
}

std::vector<GameObject*>* StageState::FindNearestGOs(Vec2 origin, std::string targetType, float range){
	vector<GameObject*> *objectsInRange= new vector<GameObject*>();
	for(unsigned int i = 0; i < objectArray.size(); i ++){
		std::unique_ptr<GameObject> &gameObjectInAnalisis= objectArray[i];
		if(nullptr != gameObjectInAnalisis){
			if(gameObjectInAnalisis->Is(targetType)){
				double distance = origin.VecDistance(gameObjectInAnalisis->box.Center()).Magnitude();
				if(distance <= range){
					objectsInRange->push_back(gameObjectInAnalisis.get());
				}
			}
		}
	}
	return(objectsInRange);
}


