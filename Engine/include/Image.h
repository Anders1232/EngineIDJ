#ifndef IMAGE_H
#define IMAGE_H

#include "Color.h"
#include "Sprite.h"
#include "Rect.h"

#include "UIelement.h"

#include <string>

class Image : public UIelement {
  public:
    Image(std::string file, UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    void Render(bool debugRender = false) const;
    float GetSpriteWidth(void);
    float GetSpriteHeight(void);
    Vec2 GetSpriteDimensions(void);
    void SetSpriteScale(float scale);
    void SetSpriteColorMultiplier(Color scale, unsigned char alpha, SDL_BlendMode blendMode = ALPHA_BLEND);
    void SetKernelSize(Vec2 kernelSize = Vec2());
  private:
    Sprite sp;
};

#endif // IMAGE_H
