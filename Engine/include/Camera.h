#ifndef CAMERA_H
#define CAMERA_H

#include "Gameobject.h"
#include "Vec2.h"

class Camera
{
	public:
		static void Follow(GameObject* newFocus);
		static void Unfollow(void);
		 static void Update(float dt);
		 static Vec2 pos;
		 static Vec2 speed;
	private:
		Camera();
		static GameObject* focus;
};

#endif // CAMERA_H
