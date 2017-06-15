#include "UIelement.h"

UIelement::UIelement(std::string file, BehaviorType behavior)
         : sp(file)
         , behavior(behavior) {}

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

void UIelement::SetOffsets(Vec2 min, Vec2 max) {
    offsets = Rect(min.x, min.y, max.x, max.y);
}

void UIelement::Update(float dt) {}

void UIelement::Render() {
    Vec2 winSize = Game::GetInstance().GetWindowDimensions();
    Rect boundingBox;
    boundingBox.x = winSize.x*anchors.x+offsets.x;
    boundingBox.y = winSize.y*anchors.y+offsets.y;
    boundingBox.w = winSize.x*anchors.w+offsets.w;
    boundingBox.h = winSize.y*anchors.h+offsets.h;

    Rect pos;
    pos.x = boundingBox.x;
    pos.y = boundingBox.y;
    float multiplier;
    float max = 1, min = 1;
    if(BehaviorType::STRETCH == behavior) {
        pos.w = boundingBox.w - boundingBox.x;
        pos.h = boundingBox.h - boundingBox.y;
    } else if(BehaviorType::FIT == behavior) {
        max = sp.GetWidth() > sp.GetHeight() ? sp.GetWidth() : sp.GetHeight();
        min = boundingBox.w - boundingBox.x < boundingBox.y - boundingBox.y ? boundingBox.w - boundingBox.x : boundingBox.y - boundingBox.y;
    } else if(BehaviorType::FILL == behavior) {
        min = sp.GetWidth() < sp.GetHeight() ? sp.GetWidth() : sp.GetHeight();
        max = boundingBox.w - boundingBox.x > boundingBox.y - boundingBox.y ? boundingBox.w - boundingBox.x : boundingBox.y - boundingBox.y;
    }
    multiplier = min/max;
    pos.w = multiplier*(boundingBox.w - boundingBox.x);
    pos.h = multiplier*(boundingBox.h - boundingBox.h);
    sp.Render(pos, 0, false);
}
