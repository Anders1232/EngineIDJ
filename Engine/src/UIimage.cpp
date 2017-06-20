#include "UIimage.h"

UIimage::UIimage(std::string file, UIelement::BehaviorType behavior)
         : UIelement(behavior) {
    sp = Sprite(file);
    SetKernelSize();
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
    SetKernelSize();
}

void UIimage::SetSpriteColorMultiplier(Color color, unsigned char alpha, SDL_BlendMode blendMode) {
    sp.colorMultiplier = color;
    sp.alpha = alpha;
    sp.blendMode = blendMode;
}

void UIimage::SetKernelSize(Vec2 kernelSize) { // É para ignorar o argumento mesmo
    this->kernelSize = Vec2(sp.GetWidth(), sp.GetHeight());
}

bool UIimage::Is(std::string UItype) const {
    return "UIimage" == UItype;
}