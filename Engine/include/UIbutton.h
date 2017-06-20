#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "Rect.h"
#include "Vec2.h"
#include "UIelement.h"

class UIbutton : public UIelement {
  public:
    enum State : int {
        DISABLED = 0,
        ENABLED,
        HIGHLIGHTED,
        SELECTED
    };
    UIbutton(UIelement::BehaviorType behavior = UIelement::BehaviorType::STRETCH, UIbutton::State initialState = UIbutton::State::ENABLED);
    const UIelement* GetUIelement(UIbutton::State whichElement) const;
    void SetUIelement(UIbutton::State whichElement, UIelement*);
    void Update(float dt, Rect parentCanvas);
    void Render(bool debugRender = false) const;
    void SetKernelSize(Vec2 kernelSize = Vec2());
    bool Is(std::string UItype) const;
    UIbutton::State actualState;
  private:
    UIelement* elements[4];
};

#endif // UIBUTTON_H
