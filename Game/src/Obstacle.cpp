#include "Obstacle.h"

Obstacle::Obstacle(std::string path, Vec2 position) : GameObject(), sp(path){
    box = position;
	// sp.ScaleX(tileSize.x/sp.GetWidth());
	// sp.ScaleY(tileSize.y/sp.GetHeight());
    box.w = sp.GetWidth();
	box.h = sp.GetHeight();
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
