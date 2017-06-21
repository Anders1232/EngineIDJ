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
    typedef void (*ButtonCallback) (void*);
    void SetCallback(UIbutton::State stateToSet, void* caller, ButtonCallback callback);
    void SetClickCallback(void* caller, ButtonCallback callback);
    virtual void SetUIbuttonState(UIbutton::State newState);
    UIbutton::State GetUIbuttonState(void) const;
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
    void* disableCaller;
    void* enabledCaller;
    void* highlightedCaller;
    void* selectedCaller;
    void* clickCaller;
};

#endif // UIBUTTON_H
