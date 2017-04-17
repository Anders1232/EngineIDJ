#ifndef CAMERA_H
#define CAMERA_H

#include "Gameobject.h"
#include "Vec2.h"

#define CAMERA_DEFAULT_MIN_ZOOM (0.3)
#define CAMERA_DEFAULT_MAX_ZOOM (5.0)
#define CAMERA_DEFAULT_ZOOMABLE (true)

class Camera
{
	public:
		static void Follow(GameObject* newFocus);
		static void Unfollow(void);
		static void Update(float dt);
		static Vec2 pos;
		static Vec2 speed;
		static void ForceZoom(float newZoom);
		static void SetZoomnable(bool zoomnable);
		static void Zoom(float deltaZoom);
		static void SetZoomLimits(float minZoom=0, float maxZoom=0);// set to 0 is to set to default
		static float GetZoom(void);
	private:
		Camera();
		static GameObject* focus;
		static float currentZoom;
		static float minZoom;
		static float maxZoom;
		static bool zoomFixed;
};

#endif // CAMERA_H
