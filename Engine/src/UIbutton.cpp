#include "UIbutton.h"

UIbutton::UIbutton(UIbutton::State initialState)
        : actualState(initialState)
        , disabledCallback(nullptr)
        , enabledCallback(nullptr)
        , highlightedCallback(nullptr)
        , selectedCallback(nullptr)
        , clickedCallback(nullptr) {}

void UIbutton::SetCallback(UIbutton::State stateToSet, ButtonCallback callback) {
    switch(actualState) {
        case UIbutton::State::DISABLED: {
            disabledCallback = callback;
            break;
        }
        case UIbutton::State::ENABLED: {
            enabledCallback = callback;
            break;
        }
        case UIbutton::State::HIGHLIGHTED: {
            highlightedCallback = callback;
            break;
        }
        case UIbutton::State::SELECTED: {
            selectedCallback = callback;
            break;
        }
    }
}

void UIbutton::SetClickCallback(ButtonCallback callback) {
    clickedCallback = callback;
}

void UIbutton::SetUIbuttonState(UIbutton::State newState) {
    actualState = newState;
    switch(actualState) {
        case UIbutton::State::DISABLED: {
            if(nullptr != disabledCallback) {
                disabledCallback(this);
            }
            break;
        }
        case UIbutton::State::ENABLED: {
            if(nullptr != enabledCallback) {
                enabledCallback(this);
            }
            break;
        }
        case UIbutton::State::HIGHLIGHTED: {
            if(nullptr != highlightedCallback) {
                highlightedCallback(this);
            }
            break;
        }
        case UIbutton::State::SELECTED: {
            if(nullptr != selectedCallback) {
                selectedCallback(this);
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
        clickedCallback(this);
    }
}

bool UIbutton::Is(std::string UItype) const {
    return "UIbutton" == UItype;
}
