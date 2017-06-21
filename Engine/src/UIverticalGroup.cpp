#include "UIverticalGroup.h"

UIverticalGroup::UIverticalGroup(UIelement::BehaviorType behavior)
        : UIcanvas(behavior) {}

void UIverticalGroup::Update(float dt, Rect parentCanvas) {
    UIcanvas::Update(dt, parentCanvas);
    if(groupedElements.size() > 0) {
        float delta = 1./groupedElements.size();
        float j = 0;
        for(unsigned int i = 0; i < groupedElements.size(); i++, j+=delta) {
            groupedElements[i]->SetAnchors( {0., j},
                                            {1., j+delta} );
        }
    }
}

bool UIverticalGroup::Is(std::string UItype) const {
    return "UIverticalGroup" == UItype || UIcanvas::Is(UItype);
}
