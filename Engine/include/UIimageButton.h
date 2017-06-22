#ifndef UIIMAGEBUTTON_H
#define UIIMAGEBUTTON_H

#include "Color.h"
#include "Sprite.h"
#include "Rect.h"

#include "UIimage.h"
#include "UIbutton.h"

#include <string>

class UIimageButton : public UIimage, public UIbutton {
  public:
    UIimageButton(UIbutton::State initialState = UIbutton::State::ENABLED, UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    virtual ~UIimageButton();
    void SetUIbuttonState(UIbutton::State newState);
    void SetStateSprite(UIbutton::State state, Sprite* sprite);
    const Sprite& GetStateSprite(UIbutton::State state) const;
    float GetStateSpriteWidth(UIbutton::State state) const;
    float GetStateSpriteHeight(UIbutton::State state) const;
    Vec2 GetStateSpriteDimensions(UIbutton::State state) const;
    void SetStateSpriteScale(UIbutton::State state, float scale);
    void SetStateSpriteColorMultiplier(UIbutton::State state, Color scale, SDL_BlendMode blendMode = ALPHA_BLEND);
    bool Is(std::string UItype) const;
  protected:
    void UpdateKernel(void);
  private:
    Sprite* disabledSprite;
    Sprite* enabledSprite;
    Sprite* highlightedSprite;
    Sprite* selectedSprite;
};

#endif // UIIMAGEBUTTON_H
