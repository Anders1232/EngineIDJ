#include "UIelement.h"

#include "Error.h"

UIelement::UIelement(std::string file, BehaviorType behavior)
         : sp(file)
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

void UIelement::SetOffsets(Vec2 min, Vec2 max) {
    offsets = Rect(min.x, min.y, max.x, max.y);
}

void UIelement::SetBehavior(BehaviorType type) {
    behavior = type;
}

void UIelement::Render(Rect parentCanvas) const {
    Rect box = ComputeBox(parentCanvas);

    sp.Render(box, 0, false);
}

Rect UIelement::ComputeBox(Rect parentCanvas) const {
    Rect boundingBox;
    boundingBox.x = parentCanvas.w*anchors.x+offsets.x;
    boundingBox.y = parentCanvas.h*anchors.y+offsets.y;
    boundingBox.w = parentCanvas.w*anchors.w+offsets.w - boundingBox.x;
    boundingBox.h = parentCanvas.h*anchors.h+offsets.h - boundingBox.y;

    Rect box;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();

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
    box.x = boundingBox.x + (boundingBox.w - box.w)/2 + parentCanvas.x;
    box.y = boundingBox.y + (boundingBox.h - box.h)/2 + parentCanvas.y;

    return box;
}
