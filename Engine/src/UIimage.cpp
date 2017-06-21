#include "UIimage.h"

UIimage::UIimage(std::string file, UIelement::BehaviorType behavior)
         : UIelement(behavior) {
    sp = Sprite(file);
    kernelSize = Vec2(sp.GetWidth(), sp.GetHeight());
}

void UIimage::Render(bool debugRender) const {
    UIelement::Render(debugRender);

    sp.Render(box, 0, false);
}

float UIimage::GetSpriteWidth(void) {
    return kernelSize.x;
}

float UIimage::GetSpriteHeight(void) {
    return kernelSize.y;
}

Vec2 UIimage::GetSpriteDimensions(void) {
    return kernelSize;
}

void UIimage::SetSpriteScale(float scale) {
    sp.SetScale(scale);
    kernelSize = Vec2(sp.GetWidth(), sp.GetHeight());
}

void UIimage::SetSpriteColorMultiplier(Color color, SDL_BlendMode blendMode) {
    sp.colorMultiplier = color;
    sp.blendMode = blendMode;
}

bool UIimage::Is(std::string UItype) const {
    return "UIimage" == UItype || UIelement::Is(UItype);
}