#include "Tower.h"

#include "Camera.h"
#include "DragAndDrop.h"
#include "Error.h"

Tower::Tower(TowerType type, Vec2 pos, Vec2 tileSize)
		: sp(type == TowerType::MEDICINE ? "img/tower/torre_fumaca.png" :
			type == TowerType::SOCIOLOGY ? "img/tower/torre_fumaca.png" :
			type == TowerType::ENGINEERING ? "img/tower/torre_fumaca.png" :
			type == TowerType::ARTS ? "img/tower/torre_fumaca.png" :
			type == TowerType::COMPUTATION ? "img/tower/torre_fumaca.png":
			"",
			true)
		, hitpoints(TOWER_BASE_HP) {
	box.x = pos.x;
	box.y = pos.y;
	sp.ScaleX(tileSize.x/sp.GetWidth());
	sp.ScaleY(tileSize.y/sp.GetHeight());
	sp.colorMultiplier = Color( 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 127 + 127*(float)rand()/RAND_MAX );
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

Tower::~Tower() {
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
}

void Tower::Damage(int damage) {
	hitpoints = hitpoints - damage;
}

void Tower::Update(float dt ) {
	for(uint count = 0; count < components.size(); count++) {
		components[count]->Update(dt);
	}
}

void Tower::Render(void) {
	sp.Render(box);
}

bool Tower::IsDead(void) {
	 return 0 >= hitpoints;
}

void Tower::RequestDelete(void) {
	hitpoints = 0;
}

void Tower::NotifyCollision(GameObject &object) {}

Rect Tower::GetWorldRenderedRect() const {
	return Camera::WorldToScreen(box);
}

bool Tower::Is(string type) {
	return "Tower" == type;
}
