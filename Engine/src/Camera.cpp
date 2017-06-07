#include "Camera.h"
#include "InputManager.h"
#include "Error.h"
#include "Game.h"

#define CAMERA_MOVE_SPEED (100)
#define INPUT_MANAGER InputManager::GetInstance()

GameObject* Camera::focus= nullptr;
Vec2 Camera::pos;
float Camera::speed= CAMERA_MOVE_SPEED;
float Camera::currentZoom= 1.0;
float Camera::minZoom= CAMERA_DEFAULT_MIN_ZOOM;
float Camera::maxZoom= CAMERA_DEFAULT_MAX_ZOOM;
bool Camera::zoomFixed= !CAMERA_DEFAULT_ZOOMABLE;
float Camera::zoomSpeed= CAMERA_DEFAULT_ZOOM_SPEED;


void Camera::Follow(GameObject* newFocus) {
	focus= newFocus;
}
void Camera::Unfollow(void) {
	focus= nullptr;
}
void Camera::Update(float dt) {
	if(nullptr != focus) {
		//centrar a câmera na tela
		pos= (focus->box).Center()- (Game::GetInstance().GetWindowDimensions()*0.5* (1./Camera::GetZoom()));
//		pos= pos * Camera::GetZoom();
	}
	else {
		if(INPUT_MANAGER.IsKeyDown(LEFT_ARROW_KEY) || INPUT_MANAGER.IsKeyDown('a')) {
			pos.x -= speed * dt;
//			if(pos.x <0 ) pos.x=0;
		}
		if(INPUT_MANAGER.IsKeyDown(RIGHT_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('d')) {
			pos.x += speed*dt;
		}
		if(INPUT_MANAGER.IsKeyDown(DOWN_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('s')) {
			pos.y += speed*dt;
//			if(pos.y <0 ) pos.y=0;
		}
		if(INPUT_MANAGER.IsKeyDown(UP_ARROW_KEY) | INPUT_MANAGER.IsKeyDown('w')) {
			pos.y -= speed*dt;
		}
	}
	if(INPUT_MANAGER.IsMouseScrolling()) {
		Camera::Zoom( (float)INPUT_MANAGER.MouseScroll().y );
	}
}

void Camera::ForceZoom(float newZoom) {
	currentZoom= newZoom;
}
void Camera::SetZoomable(bool zoomable) {
	zoomFixed= !zoomable;
}
void Camera::Zoom(float deltaZoom) {
	if(!zoomFixed) {
		currentZoom+= deltaZoom*zoomSpeed;
		if(maxZoom < currentZoom) {
			currentZoom= maxZoom;
		}
		else if(minZoom > currentZoom) {
			currentZoom= minZoom;
		}
	}
}
void Camera::SetZoomLimits(float minZoom, float maxZoom) {
	Camera::minZoom= (minZoom == 0)? CAMERA_DEFAULT_MIN_ZOOM : minZoom;
	Camera::maxZoom= (maxZoom == 0)? CAMERA_DEFAULT_MAX_ZOOM : maxZoom;
}
float Camera::GetZoom(void) {
	return currentZoom;
}

void Camera::SetZoomSpeed(float newZoomSpeed) {
	zoomSpeed= newZoomSpeed;
}

Vec2 Camera::WorldToScreen(Vec2 world) {
	Vec2 screen = world-pos;
	screen.x *= currentZoom;
	screen.y *= currentZoom;
	return screen;
}

Rect Camera::WorldToScreen(Rect world) {
	Rect screen;
	screen.x = (world.x-pos.x)*currentZoom;
	screen.y = (world.y-pos.y)*currentZoom;
	screen.w *= currentZoom;
	screen.h *= currentZoom;
	return screen;
}

Vec2 Camera::ScreenToWorld(Vec2 screen) {
	Vec2 world;
	world.x = screen.x/currentZoom;
	world.y = screen.y/currentZoom;
	world = world+pos;
	return world;
}

Rect Camera::ScreenToWorld(Rect screen) {
	Rect world;
	world.x = (screen.x/currentZoom)+pos.x;
	world.y = (screen.y/currentZoom)+pos.y;
	world.w = screen.w/currentZoom;
	world.h = screen.h/currentZoom;
	return world;
}
