#include "UItextButton.h"

#include "Error.h"

UItextButton::UItextButton( string fontFile,
                            int fontSize,
                            UItext::TextStyle style,
                            SDL_Color color,
                            string text,
                            UIelement::BehaviorType behavior,
                            bool isStrobing)
        : UItext(fontFile, fontSize, style, color, text, behavior, isStrobing)
        , UIbutton()
        , disabledColor(color)
        , enabledColor(color)
        , highlightedColor(color)
        , selectedColor(color) {}

void UItextButton::ConfigColors(SDL_Color disabled, SDL_Color enabled, SDL_Color highlighted, SDL_Color selected) {
    disabledColor = disabled;
    enabledColor = enabled;
    highlightedColor = highlighted;
    selectedColor = selected;
    SetColor(GetStateColor(actualState));
}

void UItextButton::SetUIbuttonState(UIbutton::State newState) {
    UIbutton::SetUIbuttonState(newState);
    switch(actualState) {
        case UIbutton::State::DISABLED : {
            SetColor(disabledColor);
            break;
        }
        case UIbutton::State::ENABLED : {
            SetColor(enabledColor);
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            SetColor(highlightedColor);
            break;
        }
        case UIbutton::State::SELECTED : {
            SetColor(selectedColor);
            break;
        }
    }
}

void UItextButton::SetStateColor(UIbutton::State state, SDL_Color color) {
    switch(state) {
        case UIbutton::State::DISABLED : {
            disabledColor = color;
            break;
        }
        case UIbutton::State::ENABLED : {
            enabledColor = color;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            highlightedColor = color;
            break;
        }
        case UIbutton::State::SELECTED : {
            selectedColor = color;
            break;
        }
    }
    if(state == actualState) {
        SetColor(color);
    }
}

SDL_Color UItextButton::GetStateColor(UIbutton::State state) const {
    switch(state) {
        case UIbutton::State::DISABLED : {
            return disabledColor;
            break;
        }
        case UIbutton::State::ENABLED : {
            return enabledColor;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            return highlightedColor;
            break;
        }
        case UIbutton::State::SELECTED : {
            return selectedColor;
            break;
        }
    }
    Error("Não deveria chegar até aqui");
    return {255,255,255,255};
}

void UItextButton::Update(float dt, Rect parentCanvas) {
    UItext::Update(dt, parentCanvas);
}

void UItextButton::Render(bool debugRender) const {
    UItext::Render(debugRender);
}

bool UItextButton::Is(std::string UItype) const {
    return "UItextButton" == UItype || UItext::Is(UItype) || UIbutton::Is(UItype);
}
