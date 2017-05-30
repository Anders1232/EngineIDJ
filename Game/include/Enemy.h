#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "Wave.h"
#include "Sprite.h"
#include "Rect.h"
#include "TileMap.h"
#include "Timer.h"

#define BASE_HIT_POINTS 100
#define DIFICULTY_CONSTANT 12



class Enemy : public GameObject
{
public:
	Enemy(Vec2 position, float lifeModifier); // calcula vida e velocidade 
	~Enemy();

	void Update(float dt);
	void Render(void);
	bool IsDead(void);
	void RequestDelete();
	void NotifyCollision(GameObject &object);
	bool Is(string type);
	Rect GetWorldRenderedRect(void) const;

private:
	enum EnemyType{ HOSTILE, NEUTRAL, ENGINEER, ARQUITET, ART, QUIMIC } type;
	Sprite sp;
	bool dead;
};

#endif
