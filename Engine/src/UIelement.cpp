#include "UIelement.h"

#include "Game.h"
#include "Error.h"

UIelement::UIelement(BehaviorType behavior)
				 : kernelSize(1,1)
				 , behavior(behavior) {
		SetAnchors( {0.,0.}, {1.,1.} );
		SetOffsets( {0.,0.}, {0.,0.} );
}

void UIelement::SetAnchors(Vec2 min, Vec2 max) {
		if(min.x < 0.) min.x = 0.;
		if(min.y < 0.) min.y = 0.;
		if(min.x > 1.) min.x = 1.;
		if(min.y > 1.) min.y = 1.;

		if(max.x < 0.) max.x = 0.;
		if(max.y < 0.) max.y = 0.;
		if(max.x > 1.) max.x = 1.;
		if(max.y > 1.) max.y = 1.;
		
		anchors = Rect(min.x, min.y, max.x, max.y);
}

Rect UIelement::GetAnchors(void) const {
	return anchors;
}

Rect UIelement::GetOffsets(void) const {
	return offsets;
}

void UIelement::SetOffsets(Vec2 min, Vec2 max) {
		offsets = Rect(min.x, min.y, max.x, max.y);
}

void UIelement::SetBehavior(BehaviorType type) {
		behavior = type;
}

void UIelement::Update(float dt, Rect parentCanvas) {
		boundingBox = ComputeBoundingbox(parentCanvas);
		box = ComputeBox();
		boundingBox.x += parentCanvas.x;
		boundingBox.y += parentCanvas.y;
		box.x += parentCanvas.x;
		box.y += parentCanvas.y;
}

void UIelement::Render(bool debugRender) const {
		if (debugRender) {
				SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, 255); // Bounding Vermelho
				SDL_Rect bounding = boundingBox;
				SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &bounding);

				SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, 255); // Box Amarelo
				SDL_Rect renderBox = box;
				SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &renderBox);
		}
}

Rect UIelement::GetBoundingBox(void) const {
		return boundingBox;
}

Rect UIelement::ComputeBoundingbox(Rect parentCanvas) {
		Rect boundingBox;
		boundingBox.x = parentCanvas.w*anchors.x+offsets.x;
		boundingBox.y = parentCanvas.h*anchors.y+offsets.y;
		boundingBox.w = parentCanvas.w*anchors.w+offsets.w - boundingBox.x;
		boundingBox.h = parentCanvas.h*anchors.h+offsets.h - boundingBox.y;
		return boundingBox;
}

Rect UIelement::ComputeBox() {
		box.w = kernelSize.x;
		box.h = kernelSize.y;

		Vec2 multiplier;
		float Mx = boundingBox.w/box.w;
		float My = boundingBox.h/box.h;

		if(BehaviorType::STRETCH == behavior) {
				multiplier = Vec2(Mx, My);
		} else if(BehaviorType::FIT == behavior) {
				float min = Mx < My ? Mx : My;
				multiplier = Vec2(min, min);
		} else if(BehaviorType::FILL == behavior) {
				float max = Mx > My ? Mx : My;
				multiplier = Vec2(max, max);
		} else {
				Error("Tipo de comportamento de UI indefinido.");
		}
		
		box.w = multiplier.x*(box.w);
		box.h = multiplier.y*(box.h);
		box.x = boundingBox.x + (boundingBox.w - box.w)/2;
		box.y = boundingBox.y + (boundingBox.h - box.h)/2;

		return box;
}

UIelement::operator Rect() const {
		return box;
}

bool UIelement::Is(std::string UItype) const {
		return "UIelement" == UItype;
}
