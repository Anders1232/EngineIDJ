#include "StageState.h"
#include "Camera.h"
#include "Collision.h"
#include "EndStateData.h"
#include "Enemy.h"
#include "Error.h"
#include "Tower.h"
#include "Game.h"
#include "GameResources.h"
#include "Obstacle.h"

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
#define TREE_1_TILESET_INDEX 70
#define TREE_2_TILESET_INDEX 71
#define TREE_3_TILESET_INDEX 72
#define POLE_TILESET_INDEX 73
#define BENCH_TILESET_INDEX 76

StageState::StageState(void)
		: State()
		, tileSet(120, 120,"map/tileset_vf.png")
		, tileMap("map/tileMap.txt", &tileSet)
		, inputManager(INPUT_MANAGER)
		, music("audio/stageState.ogg")
		, isLightning(false)
		, lightningTimer()
		, lightningColor(255, 255, 255, 0),
		frameRateCounter(0){
		
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

	/*
	70 a 72 3 tipos de arvores
	73 poste
	76 banco
	*/
	Vec2 obstaclePos;
	int index;
	vector<vector<int>>* tree1Tiles = tileMap.GetTileGroups(TREE_1_TILESET_INDEX);
	vector<vector<int>>* tree2Tiles = tileMap.GetTileGroups(TREE_2_TILESET_INDEX);
	vector<vector<int>>* tree3Tiles = tileMap.GetTileGroups(TREE_3_TILESET_INDEX);
	vector<vector<int>>* poleTiles = tileMap.GetTileGroups(POLE_TILESET_INDEX);
	vector<vector<int>>* benchTiles = tileMap.GetTileGroups(BENCH_TILESET_INDEX);
	for(uint i = 0; i < tree1Tiles->size(); i++){
		for(uint j = 0; j < tree1Tiles->at(i).size(); j++){
			index = tree1Tiles->at(i)[j];
			obstaclePos = Vec2(index % tileMap.GetWidth(), index / tileMap.GetWidth());
			Obstacle* tree1 = new Obstacle("./img/obstacle/arvore1.png", obstaclePos, index);
			tileMap.InsertGO(tree1, false);
			// AddObject(tree1);
			AddObstacle(tree1);
		}
	}
	for(uint i = 0; i < tree2Tiles->size(); i++){
		for(uint j = 0; j < tree2Tiles->at(i).size(); j++){
			index = tree2Tiles->at(i)[j];
			obstaclePos = Vec2(index % tileMap.GetWidth(), index / tileMap.GetWidth());
			Obstacle* tree2 = new Obstacle("./img/obstacle/arvore2.png", obstaclePos, index);
			tileMap.InsertGO(tree2, false);
			// AddObject(tree2);
			AddObstacle(tree2);
		}
	}
	for(uint i = 0; i < tree3Tiles->size(); i++){
		for(uint j = 0; j < tree3Tiles->at(i).size(); j++){
			index = tree3Tiles->at(i)[j];
			obstaclePos = Vec2(index % tileMap.GetWidth(), index / tileMap.GetWidth());
			Obstacle* tree3 = new Obstacle("./img/obstacle/arvore4.png", obstaclePos, index);
			tileMap.InsertGO(tree3, false);
			// AddObject(tree3);
			AddObstacle(tree3);
		}
	}
	for(uint i = 0; i < poleTiles->size(); i++){
		for(uint j = 0; j < poleTiles->at(i).size(); j++){
			index = poleTiles->at(i)[j];
			obstaclePos = Vec2(index % tileMap.GetWidth(), index / tileMap.GetWidth());
			Obstacle* pole = new Obstacle("./img/obstacle/posteLuz.png", obstaclePos, index);
			tileMap.InsertGO(pole, false);
			// AddObject(pole);
			AddObstacle(pole);
		}
	}
	for(uint i = 0; i < benchTiles->size(); i++){
		for(uint j = 0; j < benchTiles->at(i).size(); j++){
			index = benchTiles->at(i)[j];
			obstaclePos = Vec2(index % tileMap.GetWidth(), index / tileMap.GetWidth());
			Obstacle* bench = new Obstacle("./img/obstacle/banco_h.png", obstaclePos, index);
			tileMap.InsertGO(bench, false);
			// AddObject(bench);
			AddObstacle(bench);
		}
	}
}

StageState::~StageState(void) {
	objectArray.clear();
	obstacleArray.clear();
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
	REPORT_DEBUG("\tFrame rate: " << Game::GetInstance().GetCurrentFramerate() << "/" << Game::GetInstance().GetMaxFramerate());
	
	//depois isolar essa lógica num componente.
	frameRateTimer.Update(dt);
	frameRateCounter++;
	if(1. <= frameRateTimer.Get()){
		std::cout<<WHERE<<"\t Frame Rate: " << (float)frameRateCounter/frameRateTimer.Get()<< END_LINE;
		frameRateCounter=0;
		frameRateTimer.Restart();
	}
}

void StageState::Render(void) const {
	//renderizar o bg
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

void StageState::AddObstacle(GameObject *obstacle) {
	obstacleArray.push_back(std::unique_ptr<GameObject>(obstacle));
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
