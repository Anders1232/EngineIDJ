#include "GameObject.h"

GameObject::~GameObject(){
}

GameObject::GameObject(void): rotation(0.){
}

void GameObject::AddComponent(Component* component){
	components.emplace_back(component);
}

void GameObject::RemoveComponent(ComponentType type){
	for(unsigned int i = 0;i < components.size();i++){
		if(components[i]->Is(type)){
			delete components[i];
			components.erase(components.begin() + i);
			return;
		}
	}
}
