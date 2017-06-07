#include "Tileset.h"
#include "Error.h"
#include "Game.h"
#include "Camera.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file): tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight) {
	REPORT_I_WAS_HERE;
	rows= tileSet.GetHeight()/tileHeight;
	columns= tileSet.GetWidth()/tileWidth;
}

void TileSet::NewRender(unsigned int index, Vec2 pos) {
	ASSERT2((unsigned int)rows*columns > index, "\tReceived "<<index<<" but tileSet has size " << (unsigned int)rows*columns );
	unsigned int desiredLine, desiredColumn;
	desiredLine = index/columns;
	desiredColumn = index%columns;
	SDL_Rect wantedSubSprite;
	wantedSubSprite.x = desiredColumn*tileWidth;
	wantedSubSprite.y = desiredLine*tileHeight;
	wantedSubSprite.w = tileWidth;
	wantedSubSprite.h = tileHeight;
	Rect destinyRect(pos.x, pos.y, tileWidth, tileHeight);
	SDL_Rect dst = Camera::WorldToScreen(destinyRect);
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), tileSet.GetTexture().get(),&wantedSubSprite, &dst);
}

void TileSet::Render(unsigned int index, float x, float y, bool zoom) {
	ASSERT2(index < (unsigned int)rows*columns, "\tReceived "<<index<<" but tileSet has size " << (unsigned int)rows*columns );
	unsigned int desiredLine, desiredColumn;
	desiredLine= index/columns;
	desiredColumn= index%columns;
	SDL_Rect wantedSubSprite;
	wantedSubSprite.x= desiredColumn*tileWidth;
	wantedSubSprite.y= desiredLine*tileHeight;
	wantedSubSprite.w= tileWidth;
	wantedSubSprite.h= tileHeight;
	Rect destinyRect(x, y, tileWidth, tileHeight);
	if(zoom) {
		destinyRect= destinyRect*Camera::GetZoom();
	}
	SDL_Rect destinyPosition= destinyRect;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), tileSet.GetTexture().get(),&wantedSubSprite, &destinyPosition);
//	REPORT_I_WAS_HERE;
}

int TileSet::GetTileHeight(void) {
	return tileHeight;
}

int TileSet::GetTileWidth(void) {
	return tileWidth;
}
