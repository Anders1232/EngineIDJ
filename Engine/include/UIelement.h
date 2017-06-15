#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Rect.h"
#include "Resources.h"
#include "Vec2.h"

#include <string>

class UIelement : public GameObject {
  public:
    enum BehaviorType {
        FIT,
        FILL,
        STRETCH
    };
    UIelement(std::string file, BehaviorType behavior = BehaviorType::STRETCH);
    void SetAnchors(Vec2 min, Vec2 max);
    void SetOffsets(Vec2 min, Vec2 max);
    void Update(float dt);
    void Render();
  private:
    Sprite sp;
    Rect anchors;
    Rect offsets;
    BehaviorType behavior;
};

#endif // UIELEMENT_H
