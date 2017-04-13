#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Sprite.h"

using std::string;

class TileSet
{
	public:
		TileSet(int tileWidth, int tileHeight, string file);
		void Render(unsigned int index, float x, float y);
		int GetTileWidth(void);
		int GetTileHeight(void);
	private:
		Sprite tileSet;
		int rows;
		int columns;
		int tileWidth;
		int tileHeight;
};

#endif // TILESET_H
