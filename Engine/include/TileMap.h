#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include "Tileset.h"

#define TILE_VAZIO -1

using std::string;

class TileMap
{
	public:
		TileMap(string file, TileSet *tileSet);
		int& At(int x, int y, int z=0) const;
		void Render(int cameraX=0, int cameraY=0) const;
		void RenderLayer(int layer, int cameraX=0, int cameraY=0) const;
		int GetWidth(void) const;
		int GetHeight(void) const;
		int GetDepth(void) const;
	private:
		void Load(string file);
		void SetTileSet(TileSet *tileSet);
		int CalculateParallaxScrolling(int num, int camera, int layer) const;
		std::vector<int> tileMatrix;
		TileSet *tileSet;
		int mapWidth;
		int mapHeight;
		int mapDepth;
};

#endif // TILEMAP_H
