#ifndef GAMEOBJECTTILEMAP_H
#define GAMEOBJECTTILEMAP_H

#include "TileMap.h"
#include "Gameobject.h"

class GameObjectTileMap : public TileMap
{
	public:
		GameObjectTileMap(string collisionTileMapFile);
		void Update(void);
	private:
		void InsertGO(GameObject*);//insere numa posição válida do tileMap
		std::vector<GameObject*> gameObjectMatrix;//bidimensional??
		GameObject *draggingGO;
};

#endif // GAMEOBJECTTILEMAP_H
