#include "Camera.h"
#include "InputManager.h"
#include "Error.h"
#include "Game.h"

<<<<<<< HEAD
#define CAMERA_MOVE_SPEED (100)
=======
#define INPUT_MANAGER InputManager::GetInstance()
>>>>>>> e5875c5e599648c41a87e8ace402ea4999f3fa08

GameObject* Camera::focus= nullptr;
Vec2 Camera::pos;
float Camera::minSpeed = CAMERA_DEFAULT_MIN_SPEED;
float Camera::maxSpeed = CAMERA_DEFAULT_MAX_SPEED;
float Camera::currentSpeed = CAMERA_DEFAULT_MIN_SPEED;
float Camera::currentZoom = 1.0;
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
<<<<<<< HEAD
	}else{
		if(ActionManager::LeftArrowAction()){
			pos.x -= speed * dt;
=======
	}
	else {
		// Normaliza o nível de zoom atual
		float zoomLevel = (currentZoom-minZoom)/(maxZoom-minZoom);
		// Interpola linearmente entre min e max baseado no nível de zoom
		float speed = zoomLevel*minSpeed + (1-zoomLevel)*maxSpeed;
		if(INPUT_MANAGER.IsKeyDown(LEFT_ARROW_KEY) || INPUT_MANAGER.IsKeyDown('a')) {
			pos.x -= speed*dt;
>>>>>>> e5875c5e599648c41a87e8ace402ea4999f3fa08
//			if(pos.x <0 ) pos.x=0;
		}
		if(ActionManager::RightArrowAction()){
			pos.x += speed*dt;
		}
		if(ActionManager::DownArrowAction()){
			pos.y += speed*dt;
//			if(pos.y <0 ) pos.y=0;
		}
		if(ActionManager::UpArrowAction()){
			pos.y -= speed*dt;
		}
	}
	if(InputManager::GetInstance().IsMouseScrolling()){
		Camera::Zoom( (float)InputManager::GetInstance().MouseScroll().y );
	}
}

void Camera::ForceZoom(float newZoom){
	currentZoom= newZoom;
}

<<<<<<< HEAD
void Camera::SetZoomable(bool zoomable){
=======
void Camera::SetZoomable(bool zoomable) {
>>>>>>> e5875c5e599648c41a87e8ace402ea4999f3fa08
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
	Camera::minZoom= (0 == minZoom)? CAMERA_DEFAULT_MIN_ZOOM : minZoom;
	Camera::maxZoom= (0 == maxZoom)? CAMERA_DEFAULT_MAX_ZOOM : maxZoom;
}

float Camera::GetZoom(void) {
	return currentZoom;
}

void Camera::SetZoomSpeed(float newZoomSpeed) {
	zoomSpeed= newZoomSpeed;
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
