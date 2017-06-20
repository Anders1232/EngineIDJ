#include "UIcanvas.h"

UIcanvas::UIcanvas(UIelement::BehaviorType behavior) : UIelement(behavior) {}

UIcanvas::UIcanvas(Vec2 aspectRatio, UIelement::BehaviorType behavior) : UIelement(behavior) {
    kernelSize = aspectRatio;
}

void UIcanvas::SetKernelSize(Vec2 kernelSize) {
    this->kernelSize = kernelSize;
}

bool UIcanvas::Is(std::string UItype) const {
    return "UIcanvas" == UItype;
}
