#include "UIelement.h"
#include "Error.h"

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
    boundingBox.w = winSize.x*anchors.w+offsets.w - boundingBox.x;
    boundingBox.h = winSize.y*anchors.h+offsets.h - boundingBox.y;

    Rect pos;
    pos.w = sp.GetWidth();
    pos.h = sp.GetHeight();

    float boundingSide = 1, posSide = 1;
    if(BehaviorType::STRETCH == behavior) {
        pos.w = boundingBox.w;
        pos.h = boundingBox.h;
    } else if(BehaviorType::FIT == behavior) {
        posSide = pos.w > pos.h ? pos.w : pos.h;
        boundingSide = boundingBox.w < boundingBox.h ? boundingBox.w : boundingBox.h;
    } else if(BehaviorType::FILL == behavior) {
        posSide = pos.w < pos.h ? pos.w : pos.h;
        boundingSide = boundingBox.w > boundingBox.h ? boundingBox.w : boundingBox.h;
    } else {
        Error("Tipo de comportamento de UI indefinido.");
    }
    
    float multiplier = boundingSide/posSide;
    pos.w = multiplier*(pos.w);
    pos.h = multiplier*(pos.h);
    pos.x = boundingBox.x + (boundingBox.w - pos.w)/2;
    pos.y = boundingBox.y + (boundingBox.h - pos.h)/2;

    sp.Render(pos, 0, false);
}
