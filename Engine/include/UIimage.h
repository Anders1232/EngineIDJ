#ifndef UIIMAGE_H
#define UIIMAGE_H

#include "Color.h"
#include "Sprite.h"
#include "Rect.h"

#include "UIelement.h"

#include <string>

class UIimage : public UIelement {
  public:
    UIimage(std::string file, UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    void Render(bool debugRender = false) const;
    float GetSpriteWidth(void);
    float GetSpriteHeight(void);
    Vec2 GetSpriteDimensions(void);
    void SetSpriteScale(float scale);
    void SetSpriteColorMultiplier(Color scale, SDL_BlendMode blendMode = ALPHA_BLEND);
    bool Is(std::string UItype) const;
  private:
    Sprite sp;
};

#endif // UIIMAGE_H
