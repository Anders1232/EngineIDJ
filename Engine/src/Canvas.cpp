#include "Canvas.h"

Canvas::Canvas(UIelement::BehaviorType behavior) : UIelement(behavior) {}

Canvas::Canvas(Vec2 aspectRatio, UIelement::BehaviorType behavior) : UIelement(behavior) {
    kernelSize = aspectRatio;
}

void Canvas::SetKernelSize(Vec2 kernelSize) {
    this->kernelSize = kernelSize;
}
