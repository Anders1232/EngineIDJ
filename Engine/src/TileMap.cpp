#include <exception>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "TileMap.h"
#include "Error.h"
#include "Camera.h"
#include "InputManager.h"

#define PAREDE 0

TileMap::TileMap(string file, TileSet *tileSet): tileSet(tileSet), gameObjectMatrix(), displayCollisionInfo(false){
	Load(file, tileMatrix, true);
	gameObjectMatrix.resize(GetWidth()*GetHeight()*GetDepth());
	for(unsigned int count=0; count < gameObjectMatrix.size(); count++){
		gameObjectMatrix[count]= nullptr;
	}
}

void TileMap::Load(string file, std::vector<int> &target, bool setOfficialSize){
	FILE *arq= fopen(file.c_str(), "r");
	ASSERT(NULL != arq);
	int mWidth, mHeight, mDepth;
	fscanf(arq, "%d,%d,%d,", &mWidth, &mHeight, &mDepth);
	if(setOfficialSize){
		mapWidth= mWidth;
		mapHeight= mHeight;
		mapDepth= mDepth;
	}
	int numbersToRead= mWidth*mHeight*mDepth;
	target.resize(numbersToRead);//assim ele não desperdiça memória nem muda de tamanho no for abaixo
	int aux;
	for(int count=0; count < numbersToRead; count++) {
		fscanf(arq, " %d,", &aux);
		target[count]= aux;
	}
}

void TileMap::SetTileSet(TileSet *tileSet){
	ASSERT(this->tileSet->GetTileHeight() <= tileSet->GetTileHeight());
	ASSERT(this->tileSet->GetTileWidth() <= tileSet->GetTileWidth());
	this->tileSet=tileSet;
}

int& TileMap::At(int x, int y, int z) const{
	int index= z*mapWidth*mapHeight + y*mapWidth + x;
	try{
		return ((int&)tileMatrix.at(index) );
	}
	catch(...){
		static const int  m1=-1;
		return (int&)m1;
	}
}

void TileMap::Render(int cameraX, int cameraY, bool parallax) const{
	for(int count =0; count < mapDepth; count++){
		if(count == COLLISION_LAYER && !displayCollisionInfo){
			continue;
		}
		RenderLayer(count, cameraX, cameraY, parallax);
	}
}
void TileMap::RenderLayer(int layer, int cameraX, int cameraY, bool parallax) const{
	for(int x=0; x < mapWidth; x++){
		for(int y=0; y < mapHeight; y++){
			REPORT_I_WAS_HERE;
			int index= At(x, y, layer);
			REPORT_I_WAS_HERE;
			if(0 <= index){
				REPORT_I_WAS_HERE;
				int destinyX, destinyY;
				if(parallax){
					destinyX= CalculateParallaxScrolling((int)x*tileSet->GetTileWidth(),cameraX, layer);
					destinyY= CalculateParallaxScrolling((int)y*tileSet->GetTileHeight(), cameraY, layer);
				}
				else{
					destinyX= x*tileSet->GetTileWidth()-cameraX;
					destinyY= y*tileSet->GetTileHeight()- cameraY;
				}
				tileSet->Render(index, destinyX, destinyY);
			}
		}
	}
}

int TileMap::CalculateParallaxScrolling(int num, int camera, int layer) const{
	return (int)(num-camera*(layer+1));
	return (int)(num-camera*(layer+1)/mapDepth );
	return (int)( (double)num*(1.0+(double)layer/(double)mapDepth) );
	return (int)( (double)num*(1.0-(double)layer/(double)mapDepth) );
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

int TileMap::GetTileMousePos(Vec2 const &mousePos, bool affecteedByZoom, int layer)const{
	Vec2 position= mousePos + Camera::pos;
	if(affecteedByZoom){
		position= position.MemberMult(Camera::GetZoom());
//		position= position*Camera::GetZoom();
	}
	int x, xDir= mapWidth-1, xEsq=0;
	int tileWidth= CalculateParallaxScrolling(tileSet->GetTileWidth(), 0, layer)-  CalculateParallaxScrolling(0, 0, layer);
	int tileHeight= CalculateParallaxScrolling(tileSet->GetTileHeight(), 0, layer)-  CalculateParallaxScrolling(0, 0, layer);
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
		x= (xEsq+xDir)/2;
		if(x*tileWidth<= position.x){
			if(position.x < (x+1)*tileWidth){
				break;
			}
			else{//x  está pra direita
				xEsq= x;
			}
		}
		else{//x está pra esquerda
			xDir= x;
		}
	}
	int y, yDir= mapHeight-1, yEsq=0;
	while(1){//uma simplesBusca binária
		y= (yEsq+yDir)/2;
		if(y*tileWidth<= position.y){
			if(position.y < (y+1)*tileHeight){
				break;
			}
			else{//y  está pra direita
				yEsq= y;
			}
		}
		else{//y está pra esquerda
			yDir= y;
		}
	}
	return y*mapWidth+x;
}

void TileMap::InsertGO(GameObject* obj){
	Vec2 mousePos= InputManager::GetInstance().GetMousePos()*(1/Camera::GetZoom());
	int position= GetTileMousePos(mousePos, false, 0);
	REPORT_DEBUG("\t position = " << position << "\t of " << mapHeight*mapWidth << " tiles.");
	if(0 > position){
		std::cout << WHERE << "[ERROR] Tried to put the gameObject on an invalid tileMap position." << END_LINE;
		obj->RequestDelete();
		return;
	}
	if(-1 == AtLayer(position, COLLISION_LAYER)){
		REPORT_DEBUG("\tInserting the gameObject at position " << position);
		gameObjectMatrix[position]= obj;
		tileMatrix[position+(COLLISION_LAYER * mapWidth*mapHeight)]= PAREDE;
		int line= position/GetWidth();
		int column= position%GetWidth();
		obj->box.x= column*tileSet->GetTileWidth();
		obj->box.y= line*tileSet->GetTileHeight();
		//TODO: aqui ajudar a box para ficar exatamente no tileMap
	}
	else if (0 > AtLayer(position, COLLISION_LAYER) ){
		REPORT_DEBUG("\ttentado inserir objeto em posição inválida, pois nela está" << tileMatrix[position+(COLLISION_LAYER * mapWidth*mapHeight)]);
		obj->RequestDelete();
	}
	else{
		REPORT_DEBUG("\ttentado inserir objeto em posição já ocupada!");
		obj->RequestDelete();
	}
}

void TileMap::ShowCollisionInfo(bool show){
	displayCollisionInfo= show;
}

bool TileMap::IsShowingCollisionInfo(){
	return displayCollisionInfo;
}

int& TileMap::AtLayer(int index2D, int layer) const{
	return (int&)tileMatrix.at(index2D + layer * mapWidth * mapHeight);
}

vector<vector<int>>* TileMap::GetSpawnPositions(void) const{
	vector<vector<int>> *spawnPoints = new vector<vector<int>>();
/*	vector<int> foundSpawnPoints();
	int countLimit= GetWidth()*GetHeight();
	int base= countLimit*COLLISION_LAYER;
	for(int i= 0; i < countLimit; i++){
		int positionToBeseach= countLimit+i;
		if(SPAWN_POINT == tileMatrix[positionToBeseach]){
			foundSpawnPoints.emplace_back(positionToBeseach);
		}
	}
	//agora que tenho todos os spawn points vou agrupá-los de acordo com suas adjacências.
	spawnPoints->emplace_back();
	for(int i=0; i < foundSpawnPoints.size(); ){
		for(int i2= 0; i2 < spawnPoints->size; i2++){
			vector<int> &vec= spawnPoints[i2];
			if(
					std::find(vec.begin(), vec.end(), foundSpawnPoints[i]+1) != vec.end()
					|| std::find(vec.begin(), vec.end(), foundSpawnPoints[i]-1) != vec.end()
					|| std::find(vec.begin(), vec.end(), foundSpawnPoints[i]+GetWidth()) != vec.end()
					|| std::find(vec.begin(), vec.end(), foundSpawnPoints[i]-GetWidth()) != vec.end()
				){
				
			}
		}
	}
*/	return spawnPoints;
}


