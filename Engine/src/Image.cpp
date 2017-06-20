#include "Image.h"

Image::Image(std::string file, UIelement::BehaviorType behavior)
         : UIelement(behavior) {
    sp = Sprite(file);
    SetKernelSize();
}

void Image::Render(bool debugRender) const {
    UIelement::Render(debugRender);

    sp.Render(box, 0, false);
}

float Image::GetSpriteWidth(void) {
    return kernelSize.x;
}

float Image::GetSpriteHeight(void) {
    return kernelSize.y;
}

Vec2 Image::GetSpriteDimensions(void) {
    return kernelSize;
}

void Image::SetSpriteScale(float scale) {
    sp.SetScale(scale);
}

void Image::SetSpriteColorMultiplier(Color color, unsigned char alpha, SDL_BlendMode blendMode) {
    sp.colorMultiplier = color;
    sp.alpha = alpha;
    sp.blendMode = blendMode;
}

void Image::SetKernelSize(Vec2 kernelSize) { // É para ignorar o argumento mesmo
    this->kernelSize = Vec2(sp.GetWidth(), sp.GetHeight());
}
