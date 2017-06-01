#include "State.h"

State::State(void): popRequested(false), quitRequested(false) {
	musicVolume = 128;
}

State::~State(void) {
}

void State::AddObject(GameObject *object) {
	objectArray.push_back(std::unique_ptr<GameObject>(object));
}

bool State::PopRequested(void) {
	return popRequested;
}

bool State::QuitRequested(void) {
	return quitRequested;
}

void State::UpdateArray(float dt) {
	for(unsigned int cont=0; cont < objectArray.size(); cont++) {
		objectArray.at(cont)->Update(dt);
		if(objectArray.at(cont)->IsDead()) {
			objectArray.erase(objectArray.begin()+cont);
			cont--;
		}
	}
	for(unsigned int cont=0; cont < musicArray.size(); cont++) {
		if(!(musicArray.at(cont)->IsOpen())) {
			musicArray.erase(musicArray.begin()+cont);
			cont--;
		}
	}
	for(unsigned int cont=0; cont < soundArray.size(); cont++) {
		if(!(soundArray.at(cont)->IsOpen())) {
			soundArray.erase(soundArray.begin()+cont);
			cont--;
		}
	}
}

void State::RenderArray(void) const {
	for(unsigned int cont=0; cont < objectArray.size(); cont++) {
		objectArray[cont]->Render();
	}
}

void State::AddSound(Sound *object) {
	soundArray.push_back(std::unique_ptr<Sound>(object));
}