#include "Camera.h"
#include "InputManager.h"
#include "Error.h"
#include "Game.h"

#define CAMERA_MOVE_SPEED (100)
#define INPUT_MANAGER InputManager::GetInstance()

GameObject* Camera::focus= nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;
float Camera::currentZoom= 1.0;
float Camera::minZoom= CAMERA_DEFAULT_MIN_ZOOM;
float Camera::maxZoom= CAMERA_DEFAULT_MAX_ZOOM;
bool Camera::zoomFixed= CAMERA_DEFAULT_ZOOMABLE;

//#define KEYPRESS

void Camera::Follow(GameObject* newFocus)
{
	focus= newFocus;
}
void Camera::Unfollow(void)
{
	focus= nullptr;
}
void Camera::Update(float dt)
{
	if(nullptr != focus)
	{
		//centrar a câmera na tela
		pos= (focus->box * Camera::GetZoom() ).Center()- (Game::GetInstance().GetWindowDimensions()*0.5)*Camera::GetZoom() ;
//		pos= pos * Camera::GetZoom();
	}
	else
	{
#ifdef KEYPRESS
		if(INPUT_MANAGER.KeyPress(LEFT_ARROW_KEY) || INPUT_MANAGER.KeyPress('a'))
#else
		if(INPUT_MANAGER.IsKeyDown(LEFT_ARROW_KEY) || INPUT_MANAGER.IsKeyDown('a'))
#endif
		{
			pos.x -= CAMERA_MOVE_SPEED * dt;
			if(pos.x <0 ) pos.x=0;
		}
#ifdef KEYPRESS
		if(INPUT_MANAGER.KeyPress(RIGHT_ARROW_KEY) | INPUT_MANAGER.KeyPress('d'))
#else
		if(INPUT_MANAGER.IsKeyDown(RIGHT_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('d'))
#endif
		{
			pos.x += CAMERA_MOVE_SPEED*dt;
		}
#ifdef KEYPRESS
		if(INPUT_MANAGER.KeyPress(DOWN_ARROW_KEY) || INPUT_MANAGER.KeyPress('s'))
#else
		if(INPUT_MANAGER.IsKeyDown(DOWN_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('s'))
#endif
		{
			pos.y += CAMERA_MOVE_SPEED*dt;
//			if(pos.y <0 ) pos.y=0;
		}
#ifdef KEYPRESS
		if(INPUT_MANAGER.KeyPress(UP_ARROW_KEY) | INPUT_MANAGER.KeyPress('w'))
#else
		if(INPUT_MANAGER.IsKeyDown(UP_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('w'))
#endif
		{
			pos.y -= CAMERA_MOVE_SPEED*dt;
		}
	}
}

void Camera::ForceZoom(float newZoom)
{
	currentZoom= newZoom;
}
void Camera::SetZoomnable(bool zoomnable)
{
	zoomFixed= zoomnable;
}
void Camera::Zoom(float deltaZoom)
{
	currentZoom+= deltaZoom;
}
void Camera::SetZoomLimits(float minZoom, float maxZoom)
{
	Camera::minZoom= (minZoom == 0)? CAMERA_DEFAULT_MIN_ZOOM : minZoom;
	Camera::maxZoom= (maxZoom == 0)? CAMERA_DEFAULT_MAX_ZOOM : maxZoom;
}
float Camera::GetZoom(void)
{
	return currentZoom;
}


