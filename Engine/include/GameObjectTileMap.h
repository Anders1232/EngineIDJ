/*
#ifndef GAMEOBJECTTILEMAP_H
#define GAMEOBJECTTILEMAP_H

#include "TileMap.h"
#include "Gameobject.h"

class GameObjectTileMap : public TileMap
{
	public:
		GameObjectTileMap(string collisionTileMapFile);
		void Update(void);
		void Render(int cameraX=0, int cameraY=0) const;
		void DragAndAddGameObject(GameObject*);
		void InsertGO(GameObject*);//insere numa posição válida do tileMap
	private:
		std::vector<GameObject*> gameObjectMatrix;//bidimensional??
		std::vector<int> collisionTileMap;
		GameObject *draggingGO;
};

#endif // GAMEOBJECTTILEMAP_H
*/
