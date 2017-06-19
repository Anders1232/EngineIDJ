#include "Camera.h"

#include "Error.h"
#include "Game.h"
#include "InputManager.h"

#include <cmath>

#define INPUT_MANAGER InputManager::GetInstance()

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0,0);
float Camera::minSpeed = CAMERA_DEFAULT_MIN_SPEED;
float Camera::maxSpeed = CAMERA_DEFAULT_MAX_SPEED;
float Camera::currentSpeed = CAMERA_DEFAULT_MIN_SPEED;
float Camera::currentZoom = 1.0;
float Camera::currentLogZoom = 1.0;
float Camera::minZoom = CAMERA_DEFAULT_MIN_ZOOM;
float Camera::minLogZoom = CAMERA_DEFAULT_MIN_LOG_ZOOM;
float Camera::maxZoom = CAMERA_DEFAULT_MAX_ZOOM;
float Camera::maxLogZoom = CAMERA_DEFAULT_MAX_LOG_ZOOM;
float Camera::zoomSpeed = CAMERA_DEFAULT_ZOOM_SPEED;
float Camera::logZoomSpeed = CAMERA_DEFAULT_LOG_ZOOM_SPEED;
bool Camera::zoomFixed = !CAMERA_DEFAULT_ZOOMABLE;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow(void) {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if(nullptr != focus) {
		// Centrar a câmera na tela
		pos= (focus->box).Center() - (Game::GetInstance().GetWindowDimensions()*0.5* (1./Camera::GetZoom()));
	} else {
		// Normaliza o nível de zoom atual
		float zoomLevel = (currentLogZoom-minLogZoom)/(maxLogZoom-minLogZoom);
		// Interpola linearmente entre min e max baseado no nível de zoom
		float speed = zoomLevel*maxSpeed + (1-zoomLevel)*minSpeed;
		if(INPUT_MANAGER.IsKeyDown(LEFT_ARROW_KEY) || INPUT_MANAGER.IsKeyDown('a')) {
			pos.x -= speed*dt;
		}
		if(ActionManager::RightArrowAction()) {
			pos.x += speed*dt;
		}
		if(ActionManager::DownArrowAction()) {
			pos.y += speed*dt;
		}
		if(ActionManager::UpArrowAction()) {
			pos.y -= speed*dt;
		}
	}
	if(InputManager::GetInstance().IsMouseScrolling()){
		Camera::Zoom( (float)InputManager::GetInstance().MouseScroll().y );
	}
}

void Camera::ForceZoom(float newZoom) {
	currentLogZoom = std::log(newZoom)/std::log(CAMERA_LOGZOOM_BASE);
}

void Camera::SetZoomable(bool zoomable) {
	zoomFixed = !zoomable;
}

void Camera::Zoom(float deltaZoom) {
	if(!zoomFixed) {
		currentLogZoom += deltaZoom*logZoomSpeed;
		if(maxLogZoom < currentLogZoom) {
			currentLogZoom = maxLogZoom;
		} else if(minLogZoom > currentLogZoom) {
			currentLogZoom = minLogZoom;
		}
	}
}

void Camera::SetZoomLimits(float minZoom, float maxZoom) {
	Camera::minLogZoom = (minZoom == 0) ? CAMERA_DEFAULT_MIN_ZOOM : minZoom;
	Camera::maxLogZoom = (maxZoom == 0) ? CAMERA_DEFAULT_MAX_ZOOM : maxZoom;
}

float Camera::GetZoom(void) {
	return std::pow(CAMERA_LOGZOOM_BASE, currentLogZoom);
}

void Camera::SetZoomSpeed(float newZoomSpeed) {
	logZoomSpeed = newZoomSpeed;
}

Vec2 Camera::WorldToScreen(Vec2 world) {
	Vec2 screen = world-pos;
	float currentZoom = GetZoom();
	screen.x *= currentZoom;
	screen.y *= currentZoom;
	return screen;
}

Rect Camera::WorldToScreen(Rect world) {
	Rect screen;
	float currentZoom = GetZoom();
	screen.x = (world.x-pos.x)*currentZoom;
	screen.y = (world.y-pos.y)*currentZoom;
	screen.w = world.w*currentZoom;
	screen.h = world.h*currentZoom;
	return screen;
}

Vec2 Camera::ScreenToWorld(Vec2 screen) {
	Vec2 world;
	float currentZoom = GetZoom();
	world.x = screen.x/currentZoom;
	world.y = screen.y/currentZoom;
	world = world+pos;
	return world;
}

Rect Camera::ScreenToWorld(Rect screen) {
	Rect world;
	float currentZoom = GetZoom();
	world.x = (screen.x/currentZoom)+pos.x;
	world.y = (screen.y/currentZoom)+pos.y;
	world.w = screen.w/currentZoom;
	world.h = screen.h/currentZoom;
	return world;
}
	
void Camera::SetSpeedLimits(float minSpeed, float maxSpeed) {
	Camera::minSpeed = (0 == minSpeed) ? CAMERA_DEFAULT_MIN_SPEED : minSpeed;
	Camera::maxSpeed = (0 == maxSpeed) ? CAMERA_DEFAULT_MAX_SPEED : maxSpeed;	
}

float Camera::GetMinSpeed(void) {
	return minSpeed;
}

float Camera::GetMaxSpeed(void) {
	return maxSpeed;
}
