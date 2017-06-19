#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Sprite.h"
#include "Rect.h"
#include "Vec2.h"

#include <string>

class UIelement {
  public:
    enum BehaviorType {
        FIT,
        FILL,
        STRETCH
    };
    UIelement(std::string file, BehaviorType behavior = BehaviorType::STRETCH);
    void SetAnchors(Vec2 min, Vec2 max);
    void SetOffsets(Vec2 min, Vec2 max);
    void SetBehavior(BehaviorType type);
    void Update(float dt);
    void Render(Rect parentCanvas) const;
    Rect ComputeBoundingbox(Rect parentCanvas) const;
    Rect ComputeBox(Rect parentCanvas) const;
    float GetSpriteWidth(void);
    float GetSpriteHeight(void);
    void SetSpriteScale(float scale);
    void SetSpriteColorMultiplier(Color scale, unsigned char alpha, SDL_BlendMode blendMode = ALPHA_BLEND);
  private:
    Sprite sp;
    Rect anchors; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    Rect offsets; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    BehaviorType behavior;
};

#endif // UIELEMENT_H
