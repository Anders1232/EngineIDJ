#include "Obstacle.h"

Obstacle::Obstacle(std::string path) : GameObject(), sp(path){
    
}

void Obstacle::Update(float dt ) {}

void Obstacle::Render(void) {
	sp.Render(box);
}

void Obstacle::NotifyCollision(GameObject &object) {}

Rect Obstacle::GetWorldRenderedRect(void) const {
	return Camera::WorldToScreen(box);
}

bool Obstacle::Is(string type) {
	return "Obstacle" == type;
}
