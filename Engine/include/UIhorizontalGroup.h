#ifndef UIHORIZONTALGROUP_H
#define UIHORIZONTALGROUP_H

#include "UIelement.h"
#include "UIcanvas.h"
#include "Rect.h"

#include <vector>
#include <string>

class UIhorizontalGroup : public UIcanvas {
  public:
    UIhorizontalGroup(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    virtual void Update(float dt, Rect parentCanvas);
    bool Is(std::string UItype) const;
    std::vector<UIelement*> groupedElements;
};

#endif // UIHORIZONTALGROUP_H
