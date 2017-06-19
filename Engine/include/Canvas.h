#ifndef CANVAS_H
#define CANVAS_H

#include "UIelement.h"

#include "Vec2.h"

class Canvas : public UIelement {
  public:
    Canvas(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    Canvas(Vec2 aspectRatio, UIelement::BehaviorType behavior = UIelement::BehaviorType::FIT);
    void SetKernelSize(Vec2 kernelSize);
};

#endif // CANVAS_H
