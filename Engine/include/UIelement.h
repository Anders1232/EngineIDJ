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
  private:
    Sprite sp;
    Rect anchors; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    Rect offsets; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    BehaviorType behavior;
    Rect ComputeBox(Rect parentCanvas) const;
};

#endif // UIELEMENT_H
