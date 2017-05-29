#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "Wave.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"


class Enemy : public GameObject
{
public:
	Enemy(int wave );
	~Enemy();

	void Update(float dt);
	void Render(void);
	bool IsDead(void);
	void RequestDelete();
	void NotifyCollision(GameObject *object);
	bool Is(string type);
	Rect GetWorldRenderedRect(void);
private:
	int hp;
	Sprite sp;
	enum { HOSTILE, NEUTRAL } type;	
};

#endif