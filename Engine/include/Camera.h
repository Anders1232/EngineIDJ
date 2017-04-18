#ifndef CAMERA_H
#define CAMERA_H

#include "Gameobject.h"
#include "Vec2.h"

#define CAMERA_DEFAULT_MIN_ZOOM (0.7)
#define CAMERA_DEFAULT_MAX_ZOOM (1.5)
#define CAMERA_DEFAULT_ZOOMABLE (true)
#define CAMERA_DEFAULT_ZOOM_SPEED (5.0)

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
		static void SetZoomSpeed(float newZoomSpeed);
	private:
		Camera();
		static GameObject* focus;
		static float currentZoom;
		static float minZoom;
		static float maxZoom;
		static bool zoomFixed;
		static float zoomSpeed;
};

#endif // CAMERA_H
