#ifndef UIVERTICALGROUP_H
#define UIVERTICALGROUP_H

#include "UIelement.h"
#include "UIcanvas.h"
#include "Rect.h"

#include <vector>
#include <string>

class UIverticalGroup : public UIcanvas {
  public:
    UIverticalGroup(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    virtual void Update(float dt, Rect parentCanvas);
    bool Is(std::string UItype) const;
    std::vector<UIelement*> groupedElements;
};

#endif // UIVERTICALGROUP_H
