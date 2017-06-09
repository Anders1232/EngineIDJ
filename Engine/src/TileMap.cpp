#include "TileMap.h"

#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>

#include "Camera.h"
#include "Error.h"
#include "InputManager.h"

#define PAREDE 0

TileMap::TileMap(string file, TileSet *tileSet)
		: tileSet(tileSet)
		, gameObjectMatrix()
		, displayCollisionInfo(false) {
	Load(file, tileMatrix, true);
	gameObjectMatrix.resize(GetWidth()*GetHeight()*GetDepth());
	for(unsigned int count = 0; count < gameObjectMatrix.size(); count++) {
		gameObjectMatrix[count] = nullptr;
	}
}

void TileMap::Load(string file, std::vector<int> &target, bool setOfficialSize) {
	FILE *arq = fopen(file.c_str(), "r");
	ASSERT(NULL != arq);
	int mWidth, mHeight, mDepth;
	fscanf(arq, "%d,%d,%d,", &mWidth, &mHeight, &mDepth);
	if(setOfficialSize){
		mapWidth = mWidth;
		mapHeight = mHeight;
		mapDepth = mDepth;
	}

	int numbersToRead = mWidth*mHeight*mDepth;
	target.resize(numbersToRead);// Assim ele não desperdiça memória nem muda de tamanho no for abaixo
	int aux;
	for(int count = 0; count < numbersToRead; count++) {
		fscanf(arq, " %d,", &aux);
		target[count] = aux;
	}
}

void TileMap::SetTileSet(TileSet *tileSet) {
	ASSERT(this->tileSet->GetTileHeight() <= tileSet->GetTileHeight());
	ASSERT(this->tileSet->GetTileWidth() <= tileSet->GetTileWidth());
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) const {
	int index = z*mapWidth*mapHeight + y*mapWidth + x;
	try {
		return ( (int&)tileMatrix.at(index) );
	} catch(...) {
		static const int  m1=-1;
		return (int&)m1;
	}
}

void TileMap::Render(Vec2 pos, bool parallax, Vec2 mouse) const {
	for(int count = 0; count < mapDepth; count++) {
		if(COLLISION_LAYER == count && !displayCollisionInfo) {
			continue;
		}
		RenderLayer(count, pos, parallax, mouse);
	}
}

void TileMap::RenderLayer(int layer, Vec2 pos, bool parallax, Vec2 mouse) const {
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			int index = At(x, y, layer);
			if (0 <= index) {
				Vec2 destination;
				if (parallax) {
					Vec2 tilePos(x*tileSet->GetTileWidth(), y*tileSet->GetTileHeight());
					destination = CalculateParallaxScrolling(tilePos, pos, layer);
				} else {
					destination = pos + Vec2(x*tileSet->GetTileWidth(), y*tileSet->GetTileHeight());
				}
				Rect tile(destination.x, destination.y, tileSet->GetTileWidth(), tileSet->GetTileHeight());
				tileSet->Render(index, destination, mouse.IsInRect(Camera::WorldToScreen(tile));
			}
		}
	}
}

Vec2 TileMap::CalculateParallaxScrolling(Vec2 num, Vec2 pos, int layer) const {
	return num-(pos+Camera::pos)*(layer+1);
	return num-(pos+Camera::pos)*((layer+1)/(double)mapDepth);
	return num*(1.0+(double)layer/(double)mapDepth);
	return num*(1.0-(double)layer/(double)mapDepth);
}

int TileMap::GetWidth(void) const {
	return mapWidth;
}

int TileMap::GetHeight(void) const {
	return mapHeight;
}

int TileMap::GetDepth(void) const {
	return mapDepth;
}

int TileMap::GetTileMousePos(Vec2 const &mousePos, bool affecteedByZoom, int layer) const {
	Vec2 position = mousePos;
	int x, xDir = mapWidth-1, xEsq = 0;
	Vec2 tileSize = CalculateParallaxScrolling( Vec2(tileSet->GetTileWidth(), tileSet->GetTileHeight()), Vec2(0, 0), layer);
	tileSize = tileSize - CalculateParallaxScrolling( Vec2(0,0), Vec2(0,0), layer);
	int tileWidth = tileSize.x;
	int tileHeight = tileSize.y;
	
	if(position.x < 0){
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -1;
	}
	
	if(position.y < 0){
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -2;
	}
	
	if(position.x >= (GetWidth()-1)* tileWidth ){
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -3;
	}
	
	if(position.y >= (GetHeight()-1)* tileHeight ){
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -4;
	}
	
	while(1){//uma simplesBusca binária
		x = (xEsq+xDir)/2;
		if(x*tileWidth <= position.x){
			if(position.x < (x+1)*tileWidth) {
				break;
			} else {
				//x  está pra direita
				xEsq = x;
			}
		} else {
			//x está pra esquerda
			xDir = x;
		}
	}
	
	int y, yDir = mapHeight-1, yEsq = 0;
	while(1){//uma simplesBusca binária
		y = (yEsq+yDir)/2;
		if(y*tileWidth <= position.y) {
			if(position.y < (y+1)*tileHeight) {
				break;
			} else {
				//y  está pra direita
				yEsq = y;
			}
		} else {
			//y está pra esquerda
			yDir = y;
		}
	}
	
	return y*mapWidth+x;
}

void TileMap::InsertGO(GameObject* obj) {
	Vec2 mousePos = Camera::ScreenToWorld(InputManager::GetInstance().GetMousePos());
	int position = GetTileMousePos(mousePos, false, 0);
	REPORT_DEBUG("\t position = " << position << "\t of " << mapHeight*mapWidth << " tiles.");
	
	if(0 > position) {
		std::cout << WHERE << "[ERROR] Tried to put the gameObject on an invalid tileMap position." << END_LINE;
		obj->RequestDelete();
		return;
	}
	
	if(-1 == AtLayer(position, COLLISION_LAYER)) {
		REPORT_DEBUG("\tInserting the gameObject at position " << position);
		gameObjectMatrix[position] = obj;
		tileMatrix[position+(COLLISION_LAYER*mapWidth*mapHeight)] = PAREDE;
		
		int line = position / GetWidth();
		int column = position % GetWidth();
		obj->box.x = column*tileSet->GetTileWidth();
		obj->box.y = line*tileSet->GetTileHeight();
		//TODO: aqui ajudar a box para ficar exatamente no tileMap
	} else if(0 > AtLayer(position, COLLISION_LAYER)) {
		REPORT_DEBUG("\ttentado inserir objeto em posição inválida, pois nela está" << tileMatrix[position+(COLLISION_LAYER * mapWidth*mapHeight)]);
		obj->RequestDelete();
	} else {
		REPORT_DEBUG("\ttentado inserir objeto em posição já ocupada!");
		obj->RequestDelete();
	}
}

void TileMap::ShowCollisionInfo(bool show) {
	displayCollisionInfo = show;
}

bool TileMap::IsShowingCollisionInfo() {
	return displayCollisionInfo;
}

int& TileMap::AtLayer(int index2D, int layer) const {
	return (int&)tileMatrix.at(index2D + layer * mapWidth * mapHeight);
}

vector<vector<int>>* TileMap::GetSpawnPositions(void) const {
	vector<vector<int>> *spawnPoints = new vector<vector<int>>();
	vector<int> foundSpawnPoints;
	uint countLimit = GetWidth()*GetHeight();
	int base = countLimit*COLLISION_LAYER;
	REPORT_I_WAS_HERE;

	for(uint i = 0; i < countLimit; i++) {
		int positionToBeseach = base+i;
		if(SPAWN_POINT == tileMatrix[positionToBeseach]) {
			foundSpawnPoints.push_back(positionToBeseach%(GetWidth()*GetHeight()));
		}
	}
	REPORT_I_WAS_HERE;
	// Agora que tenho todos os spawn points vou agrupá-los de acordo com suas adjacências.
	if(foundSpawnPoints.empty()) {
		Error("Não foi encontrado spawn points!");
	}

	spawnPoints->emplace_back();
	(*spawnPoints)[0].push_back(foundSpawnPoints[0]);
	foundSpawnPoints.erase(foundSpawnPoints.begin());
	while(!foundSpawnPoints.empty()) {
		bool neighborFound = false;
		for(unsigned int i = 0; i < spawnPoints->size(); i++) {
			vector<int> &vec = (*spawnPoints)[i];
			if(
					(std::find(vec.begin(), vec.end(), foundSpawnPoints[0]+1) != vec.end() )//posição à direita
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]-1) != vec.end() )//posição à esquerda
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]+GetWidth()) != vec.end() )// posição em cima
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]-GetWidth()) != vec.end() )//posição em baixo
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]-GetWidth()-1) != vec.end() )//diagonal supeior esquerda
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]-GetWidth()+1) != vec.end() )//diagonal supeior direita
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]+GetWidth()-1) != vec.end() )//diagonal inferior esquerda
					|| (std::find(vec.begin(), vec.end(), foundSpawnPoints[0]+GetWidth()+1) != vec.end() )//diagonal inferior direita
			){
				vec.push_back(foundSpawnPoints[0]);
				foundSpawnPoints.erase(foundSpawnPoints.begin());
				neighborFound = true;
				break;
			}
		}
		
		if(!neighborFound) {
			spawnPoints->emplace_back();
			(*spawnPoints)[spawnPoints->size()-1].push_back(foundSpawnPoints[0]);
			foundSpawnPoints.erase(foundSpawnPoints.begin());
		}
		REPORT_I_WAS_HERE;
	}
#ifdef DEBUG
	std::cout << WHERE << "\tNumero de spawn groups achados: " << (*spawnPoints).size() << END_LINE;
	for(uint i = 0; i < (*spawnPoints).size(); i++) {
		std::cout << WHERE << "\tSpawn groups " << i <<" tem tamanho " << (*spawnPoints)[i].size() << END_LINE;
		std::cout << WHERE << "\tTileWidth= " << GetWidth() << END_LINE;
		for(uint i2 = 0; i2 < (*spawnPoints)[i].size(); i2++) {
			std::cout << WHERE << "\tSpawn point: " << (*spawnPoints)[i][i2] << END_LINE;
		}
	}
#endif
	return spawnPoints;
}

Vec2 TileMap::GetTileSize(void) const{
	return Vec2(tileSet->GetTileWidth(), tileSet->GetTileHeight());
}
