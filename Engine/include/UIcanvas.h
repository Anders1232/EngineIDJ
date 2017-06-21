#ifndef UICANVAS_H
#define UICANVAS_H

#include "UIelement.h"

#include "Vec2.h"

#include <string>

class UIcanvas : public UIelement {
  public:
    UIcanvas(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    UIcanvas(Vec2 aspectRatio, UIelement::BehaviorType behavior = UIelement::BehaviorType::FIT);
    void SetAspectRatio(Vec2 aspectRatio);
    bool Is(std::string UItype) const;
};

#endif // UICANVAS_H
