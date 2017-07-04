#ifndef TILEMAPOBSERVER_H
#define TILEMAPOBSERVER_H

class TileMapObserver{
	public:
		virtual void NotifyTileMapChanged(void)=0;
};

#endif // TILEMAPOBSERVER_H
