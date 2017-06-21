#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "Rect.h"
#include "Vec2.h"

#include <string>

class UIbutton {
  public:
    enum State : int {
        DISABLED = 0,
        ENABLED,
        HIGHLIGHTED,
        SELECTED
    };
    typedef void (*ButtonCallback) (UIbutton*);
    void SetCallback(UIbutton::State stateToSet, ButtonCallback callback);
    void SetClickCallback(ButtonCallback callback);
    void SetUIbuttonState(UIbutton::State newState);
    UIbutton::State GetUIbuttonState(void);
    void Click();
    virtual bool Is(std::string UItype) const;
  protected:
    UIbutton(UIbutton::State initialState = UIbutton::State::ENABLED);
    UIbutton::State actualState;
    ButtonCallback disabledCallback;
    ButtonCallback enabledCallback;
    ButtonCallback highlightedCallback;
    ButtonCallback selectedCallback;
    ButtonCallback clickedCallback;
};

#endif // UIBUTTON_H
