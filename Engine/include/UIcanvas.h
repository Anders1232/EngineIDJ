#ifndef UICANVAS_H
#define UICANVAS_H

#include "UIelement.h"

#include "Vec2.h"

#include <string>

class UIcanvas : public UIelement {
  public:
    UIcanvas(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    UIcanvas(Vec2 aspectRatio, UIelement::BehaviorType behavior = UIelement::BehaviorType::FIT);
    void SetKernelSize(Vec2 kernelSize);
    bool Is(std::string UItype) const;
};

#endif // UICANVAS_H
