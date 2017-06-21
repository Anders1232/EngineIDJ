#include "UIbutton.h"

UIbutton::UIbutton(UIbutton::State initialState)
        : actualState(initialState)
        , disabledCallback(nullptr)
        , enabledCallback(nullptr)
        , highlightedCallback(nullptr)
        , selectedCallback(nullptr)
        , clickedCallback(nullptr) {}

void UIbutton::SetCallback(UIbutton::State stateToSet, void* caller, ButtonCallback callback) {
    switch(actualState) {
        case UIbutton::State::DISABLED: {
            disabledCallback = callback;
            disableCaller = caller;
            break;
        }
        case UIbutton::State::ENABLED: {
            enabledCallback = callback;
            enabledCaller = caller;
            break;
        }
        case UIbutton::State::HIGHLIGHTED: {
            highlightedCallback = callback;
            highlightedCaller = caller;
            break;
        }
        case UIbutton::State::SELECTED: {
            selectedCallback = callback;
            selectedCaller = caller;
            break;
        }
    }
}

void UIbutton::SetClickCallback(void* caller, ButtonCallback callback) {
    clickedCallback = callback;
    clickCaller = caller;
}

void UIbutton::SetUIbuttonState(UIbutton::State newState) {
    actualState = newState;
    switch(actualState) {
        case UIbutton::State::DISABLED: {
            if(nullptr != disabledCallback) {
                disabledCallback(disableCaller);
            }
            break;
        }
        case UIbutton::State::ENABLED: {
            if(nullptr != enabledCallback) {
                enabledCallback(enabledCaller);
            }
            break;
        }
        case UIbutton::State::HIGHLIGHTED: {
            if(nullptr != highlightedCallback) {
                highlightedCallback(highlightedCaller);
            }
            break;
        }
        case UIbutton::State::SELECTED: {
            if(nullptr != selectedCallback) {
                selectedCallback(selectedCaller);
            }
            break;
        }
    }
}

UIbutton::State UIbutton::GetUIbuttonState(void) const {
    return actualState;
}

void UIbutton::Click() {
    if(nullptr != clickedCallback) {
        clickedCallback(clickCaller);
    }
}

bool UIbutton::Is(std::string UItype) const {
    return "UIbutton" == UItype;
}
