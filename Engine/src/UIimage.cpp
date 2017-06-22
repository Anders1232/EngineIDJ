#include "UIimage.h"

#include "Error.h"

UIimage::UIimage(std::string file, UIelement::BehaviorType behavior)
         : UIelement(behavior) {
    sp = new Sprite(file);
    kernelSize = Vec2(sp->GetWidth(), sp->GetHeight());
}

UIimage::UIimage(UIelement::BehaviorType behavior) : UIelement(behavior), sp(nullptr) {}

UIimage::~UIimage() {
    if(nullptr != sp) {
        delete sp;
    }
}

void UIimage::Render(bool debugRender) const {
    UIelement::Render(debugRender);

    if(nullptr != sp) {
        sp->Render(box, 0, false);
    } else {
        Error("Alguma classe filha de UIimage não foi corretamente inicializada.")
    }
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
    sp->SetScale(scale);
    kernelSize = Vec2(sp->GetWidth(), sp->GetHeight());
}

void UIimage::SetSpriteColorMultiplier(Color color, SDL_BlendMode blendMode) {
    sp->colorMultiplier = color;
    sp->blendMode = blendMode;
}

bool UIimage::Is(std::string UItype) const {
    return "UIimage" == UItype || UIelement::Is(UItype);
}