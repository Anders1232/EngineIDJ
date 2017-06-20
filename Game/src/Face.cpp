#include "Face.h"

#include "Camera.h"
#include "DragAndDrop.h"
#include "Error.h"

typedef unsigned int uint;

Face::Face(float x, float y, Vec2 tileSize, TileMap *tileMap)
		: sp("img/tower/torre_fumaca.png", true)
		, hitpoints(FACE_HP) {
	box.x = x;
	box.y = y;
	sp.ScaleX(tileSize.x/sp.GetWidth()*4);
	sp.ScaleY(tileSize.y/sp.GetHeight()*4);
	sp.colorMultiplier = Color( 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX, 255*(float)rand()/RAND_MAX );
	sp.alpha = 255*(float)rand()/RAND_MAX;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	components.emplace_back( new DragAndDrop(tileMap,*this, true, true) );
}

Face::~Face() {
	for(uint i = 0; i < components.size(); i++) {
		delete components[i];
	}
	components.clear();
}

void Face::Damage(int damage) {
	hitpoints = hitpoints - damage;
}

void Face::Update(float dt ) {
	for(uint count = 0; count < components.size(); count++) {
		components[count]->Update(dt);
	}
}

void Face::Render(void) {
	sp.Render(box);
}

bool Face::IsDead(void) {
	 return 0 >= hitpoints;
}

void Face::RequestDelete(void) {
	hitpoints = 0;
}

void Face::NotifyCollision(GameObject &other) {}

Rect Face::GetWorldRenderedRect() const {
	return Camera::WorldToScreen(box);
}

bool Face::Is(string type) {
	return "Face" == type;
}
