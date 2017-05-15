#include "InputManager.h"
#include "string.h"
#include "Error.h"
//#include "Camera.h"

InputManager::InputManager():quitRequested(false), updateCounter(0), mouseX(0), mouseY(0), mouseScroolUpdate(0) {
	memset(keyState, 0, 416*sizeof(bool));
	memset(keyUpdate, 0, 416*sizeof(int));
	memset(mouseState, 0, 6*sizeof(bool));
	memset(mouseUpdate, 0, 6*sizeof(int));
}
InputManager::~InputManager() {
}
InputManager& InputManager::GetInstance(void) {
	static InputManager inputManager;
	return inputManager;
}

#define AJUST_KEY(k)if(k >= 0x40000000) {\
	k=k-0x40000000+0x7F;\
}

void InputManager::Update(void) {
	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested= false;
	updateCounter++;
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(SDL_KEYDOWN == event.type) {
			if(!event.key.repeat) {
				int keyCode= event.key.keysym.sym;
				AJUST_KEY(keyCode);
				keyState[keyCode]= true;
				keyUpdate[keyCode]= updateCounter;
			}
		}
		else if (SDL_KEYUP == event.type) {
			if(!event.key.repeat) {
				int keyCode= event.key.keysym.sym;
				AJUST_KEY(keyCode);
				keyState[keyCode]= false;
				keyUpdate[keyCode]= updateCounter;
			}
		}
		else if(SDL_MOUSEBUTTONDOWN == event.type) {
			mouseState[event.button.button]= true;
			mouseUpdate[event.button.button]= updateCounter;
		}
		else if(SDL_MOUSEBUTTONUP == event.type) {
			mouseState[event.button.button]= false;
			mouseUpdate[event.button.button]= updateCounter;
		}
		else if(SDL_QUIT == event.type) {
			quitRequested=true;
		}
		else if(SDL_MOUSEWHEEL == event.type) {
			mouseScroolState= Vec2(event.wheel.x, event.wheel.y);
			mouseScroolUpdate= updateCounter;
		}
	}
}

bool InputManager::KeyPress(int key) const {
	AJUST_KEY(key);
	return keyState[key] && keyUpdate[key] == updateCounter;
}
bool InputManager::KeyRelease(int key) const {
	AJUST_KEY(key);
	return ((false==keyState[key]) && keyUpdate[key] ==updateCounter);
}
bool InputManager::IsKeyDown(int key) const {
	AJUST_KEY(key);
	return keyState[key];
}
bool InputManager::MousePress(int button) const {
	return mouseState[button]&& mouseUpdate[button]== updateCounter;
}
bool InputManager::MouseRelease(int button) const {
	return ((false == mouseState[button]) && mouseUpdate[button] == updateCounter);
}
bool InputManager::IsMouseDown(int button) const {
	return mouseState[button];
}
int InputManager::GetMouseX(void) const {
	return mouseX;
}
int InputManager::GetMouseY(void) const {
	return mouseY;
}
bool InputManager::QuitRequested(void) const {
	return quitRequested;
}
Vec2 InputManager::GetMousePos() const {
	return Vec2(mouseX, mouseY);
}
Vec2 InputManager::MouseScroll(void) const {
	return mouseScroolState;
}
bool InputManager::IsMouseScrolling(void) const {
	return (mouseScroolUpdate == updateCounter);
}


