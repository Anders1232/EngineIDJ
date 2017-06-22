#ifndef UIGRIDGROUP_H
#define UIGRIDGROUP_H

#include "UIelement.h"
#include "UIcanvas.h"
#include "Rect.h"

#include <vector>
#include <string>

class UIgridGroup : public UIcanvas {
  public:
    enum ConstraintType {
      FIXED_N_ROWS,
      FIXED_N_COLS
    }
    UIgridGroup(UIgridGroup::ConstraintType constraintType, int number, UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH);
    virtual void Update(float dt, Rect parentCanvas);
    void SetConstraint(UIgridGroup::ConstraintType newConstraint, int value);
    bool Is(std::string UItype) const;
    std::vector<UIelement*> groupedElements;
  private:
    UIgridGroup::ConstraintType constraint;
    int number;
};

#endif // UIGRIDGROUP_H
