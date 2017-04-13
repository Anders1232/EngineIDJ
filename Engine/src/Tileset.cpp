#include "Tileset.h"
#include "Error.h"
#include "Game.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file): tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight)
{
	REPORT_I_WAS_HERE;
	rows= tileSet.GetHeight()/tileHeight;
	columns= tileSet.GetWidth()/tileWidth;
}

void TileSet::Render(unsigned int index, float x, float y)
{
	ASSERT(index < (unsigned int)rows*columns);
	unsigned int desiredLine, desiredColumn;
	desiredLine= index/columns;
	desiredColumn= index%columns;
	SDL_Rect wantedSubSprite;
	wantedSubSprite.x= desiredColumn*tileWidth;
	wantedSubSprite.y= desiredLine*tileHeight;
	wantedSubSprite.w= tileWidth;
	wantedSubSprite.h= tileHeight;
	SDL_Rect destinyPosition;
	destinyPosition.x=x;
	destinyPosition.y=y;
	destinyPosition.w= tileWidth;
	destinyPosition.h= tileHeight;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), tileSet.GetTexture().get(),&wantedSubSprite, &destinyPosition);
//	REPORT_I_WAS_HERE;
}

int TileSet::GetTileHeight(void)
{
	return tileHeight;
}

int TileSet::GetTileWidth(void)
{
	return tileWidth;
}
