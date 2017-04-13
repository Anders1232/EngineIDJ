#ifndef ALIEN_H
#define ALIEN_H

#include "Minion.h"
#include "Gameobject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Timer.h"
#include <queue>
#include <vector>

#define ALIEN_MOVE_SPEED (300)
#define MIN_DISTANCE_BETWEEN_ALIENS (100)

using std::queue;
using std::vector;

class Alien: public GameObject
{
	public:
		Alien(float X, float y, int nMinions);
		~Alien(void);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(string type);
		static int alienCount;
	private:
		enum AlienState
		{
			MOVING,
			RESTING
		} state;
		Sprite sp;
		Vec2 speed;
		int hp;
		vector<Minion> minionArray;
		Timer restTimer;
		Vec2 destination;
		int GetNearestMinion(Vec2 targetPos);
		float alienRestingCooldown;
		float CalculateRestingCooldown(void);
		float lastDistance;
};


#endif // ALIEN_H
