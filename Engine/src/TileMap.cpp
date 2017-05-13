#include <exception>
#include <cstdio>
#include <iostream>
#include "TileMap.h"
#include "Error.h"
#include "Camera.h"

TileMap::TileMap(string file, TileSet *tileSet): tileSet(tileSet) {
	Load(file);
}

void TileMap::Load(string file) {
	FILE *arq= fopen(file.c_str(), "r");
	ASSERT(NULL != arq);
	fscanf(arq, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
	int numbersToRead= mapWidth*mapHeight*mapDepth;
	tileMatrix.resize(numbersToRead);//assim ele não desperdiça memória nem muda de tamanho no for abaixo
	int aux;
	for(int count=0; count < numbersToRead; count++) {
		fscanf(arq, " %d,", &aux);
		tileMatrix[count]= aux-1;
	}
}

void TileMap::SetTileSet(TileSet *tileSet) {
	ASSERT(this->tileSet->GetTileHeight() <= tileSet->GetTileHeight());
	ASSERT(this->tileSet->GetTileWidth() <= tileSet->GetTileWidth());
	this->tileSet=tileSet;
}

int& TileMap::At(int x, int y, int z) const {
//	int* vec= (int*)tileMatrix.data();
//	return (vec[z*mapWidth*mapHeight + y*mapWidth + x]);
	int index= z*mapWidth*mapHeight + y*mapWidth + x;
	try {
		return ((int&)tileMatrix.at(index) );
	}
	catch(...) {
		static const int  m1=-1;
		return (int&)m1;
	}
}

void TileMap::Render(int cameraX, int cameraY) const {
	for(int count =0; count < mapDepth; count++) {
		RenderLayer(count, cameraX, cameraY);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) const {
	for(int x=0; x < mapWidth; x++) {
		for(int y=0; y < mapHeight; y++) {
			REPORT_I_WAS_HERE;
			int index= At(x, y, layer);
			REPORT_I_WAS_HERE;
			if(0 <= index) {
				REPORT_I_WAS_HERE;
				int destinyX= CalculateParallaxScrolling((int)x*tileSet->GetTileWidth(),cameraX, layer);
				int destinyY= CalculateParallaxScrolling((int)y*tileSet->GetTileHeight(), cameraY, layer);
				tileSet->Render(At(x, y, layer), destinyX, destinyY);
			}
		}
	}
}

int TileMap::CalculateParallaxScrolling(int num, int camera, int layer) const {
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

int TileMap::GetTileMousePos(Vec2 const &mousePos, bool affecteedByZoom, int layer)const
{
	Vec2 position= mousePos + Camera::pos;
	if(affecteedByZoom)
	{
		position= position.MemberMult(Camera::GetZoom());
//		position= position*Camera::GetZoom();
	}
	int x, xDir= mapWidth-1, xEsq=0;
	int tileWidth= CalculateParallaxScrolling(tileSet->GetTileWidth(), 0, layer)-  CalculateParallaxScrolling(0, 0, layer);
	int tileHeight= CalculateParallaxScrolling(tileSet->GetTileHeight(), 0, layer)-  CalculateParallaxScrolling(0, 0, layer);
	if(position.x < 0)
	{
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -1;
	}
	if(position.y < 0)
	{
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -2;
	}
	if(position.x >= (GetWidth()-1)* tileWidth )
	{
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -3;
	}
	if(position.y >= (GetHeight()-1)* tileHeight )
	{
		std::cerr << WHERE << "Devo lançar exceção aqui?" << endl;
		return -4;
	}
	while(1)//uma simplesBusca binária
	{
		x= (xEsq+xDir)/2;
		if(x*tileWidth<= position.x)
		{
			if(position.x < (x+1)*tileWidth)
			{
				break;
			}
			else//x  está pra direita
			{
				xEsq= x;
			}
		}
		else
		{//x está pra esquerda
			xDir= x;
		}
	}
	int y, yDir= mapHeight-1, yEsq=0;
	while(1)//uma simplesBusca binária
	{
		y= (yEsq+yDir)/2;
		if(y*tileWidth<= position.y)
		{
			if(position.y < (y+1)*tileHeight)
			{
				break;
			}
			else//y  está pra direita
			{
				yEsq= y;
			}
		}
		else
		{//y está pra esquerda
			yDir= y;
		}
	}
	return y*mapWidth+x;
}

