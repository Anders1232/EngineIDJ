#include "UIgridGroup.h"

UIgridGroup::UIgridGroup(UIgridGroup::ConstraintType constraintType, int number, UIelement::BehaviorType behavior)
        : UIcanvas(behavior)
        , constraint(constraintType)
        , number(number) {}

void UIgridGroup::Update(float dt, Rect parentCanvas) {
    UIcanvas::Update(dt, parentCanvas);
    if(groupedElements.size() > 0) {
        float delta = 1./groupedElements.size();
        float j = 0;
        for(unsigned int i = 0; i < groupedElements.size(); i++, j+=delta) {
            groupedElements[i]->SetAnchors( {j, 0.},
                                            {j+delta, 1.} );
        }
    }
}

bool UIgridGroup::Is(std::string UItype) const {
    return "UIgridGroup" == UItype || UIcanvas::Is(UItype);
}
