#ifndef WAVE_H
#define WAVE_H

#include "GameObject.h"

class Wave : public GameObject
{
public:
	Wave();
	~Wave();

	void Update(float dt);
	void Render(void);
	bool IsDead(void);
	void RequestDelete();
	void NotifyCollision(GameObject *object);
	bool Is(string type);
	Rect GetWorldRenderedRect(void);


	int waveCount;

};

#endif