#include "UIgridGroup.h"

UIgridGroup::UIgridGroup(UIgridGroup::ConstraintType constraintType, int number, UIgridGroup::BehaviorOnLess behaviorOnLess, UIelement::BehaviorType behavior)
		: UIcanvas(behavior)
		, constraint(constraintType)
		, number(number)
		, behaviorOnLess(behaviorOnLess) {
	number = (number > 1.) ? number : 1.;
}

void UIgridGroup::SetConstraint(UIgridGroup::ConstraintType newConstraint, int value) {
	constraint = newConstraint;
	number = (number > 1.) ? number : 1.;
}

void UIgridGroup::Update(float dt, Rect parentCanvas) {
	UIcanvas::Update(dt, parentCanvas);
	if(groupedElements.size() > 0) {
		int numRows = (ConstraintType::FIXED_N_ROWS == constraint) ? number : std::ceil((float)groupedElements.size()/number);
		int numCols = (ConstraintType::FIXED_N_COLS == constraint) ? number : std::ceil((float)groupedElements.size()/number);
		float deltaX = 1./numCols;
		float deltaY = 1./numRows;
		float y = 0;
		unsigned int index = 0;
		for(int j = 0; j < numRows; j++, y+=deltaY) {
			float x = 0;
			int rem = (groupedElements.size() - 1) - index;
			if(rem < numCols) {
				if(UIgridGroup::BehaviorOnLess::STRETCH == behaviorOnLess) {
					deltaX = 1./rem;
				} else if(UIgridGroup::BehaviorOnLess::CENTER == behaviorOnLess) {
					x = (numCols-rem)*deltaX/2.;
				}
			}
			for(int i = 0; i < numCols; i++, x+=deltaX) {
				index = i+j*numCols;
				if(index >= groupedElements.size()) return;
				groupedElements[index]->SetAnchors( {x, y},
													{x+deltaX, y+deltaY} );
			}
		}
	}
}

bool UIgridGroup::Is(std::string UItype) const {
	return "UIgridGroup" == UItype || UIcanvas::Is(UItype);
}
