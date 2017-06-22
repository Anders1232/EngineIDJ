#include "UIimageButton.h"

#include "Error.h"

UIimageButton::UIimageButton(UIbutton::State initialState, UIelement::BehaviorType behavior)
         : UIimage(behavior)
         , UIbutton(initialState)
         , disabledSprite(nullptr)
         , enabledSprite(nullptr)
         , highlightedSprite(nullptr)
         , selectedSprite(nullptr) {}

UIimageButton::~UIimageButton() {
    sp = nullptr;
    if(nullptr != disabledSprite) {
        delete disabledSprite;
    }
    if(nullptr != enabledSprite) {
        delete enabledSprite;
    }
    if(nullptr != highlightedSprite) {
        delete highlightedSprite;
    }
    if(nullptr != selectedSprite) {
        delete selectedSprite;
    }
}

void UIimageButton::SetUIbuttonState(UIbutton::State newState) {
    switch(newState) {
        case UIbutton::State::DISABLED : {
            sp = disabledSprite;
            break;
        }
        case UIbutton::State::ENABLED : {
            sp = enabledSprite;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            sp = highlightedSprite;
            break;
        }
        case UIbutton::State::SELECTED : {
            sp = selectedSprite;
            break;
        }
    }
    UpdateKernel();
    UIbutton::SetUIbuttonState(newState);
}

void UIimageButton::SetStateSprite(UIbutton::State state, Sprite* sprite) {
    switch(state) {
        case UIbutton::State::DISABLED : {
            delete disabledSprite;
            disabledSprite = sprite;
            break;
        }
        case UIbutton::State::ENABLED : {
            delete enabledSprite;
            enabledSprite = sprite;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            delete highlightedSprite;
            highlightedSprite = sprite;
            break;
        }
        case UIbutton::State::SELECTED : {
            delete selectedSprite;
            selectedSprite = sprite;
            break;
        }
    }
    if(state == actualState) {
        sp = sprite;
        UpdateKernel();
    }
}

const Sprite& UIimageButton::GetStateSprite(UIbutton::State state) const {
    switch(state) {
        case UIbutton::State::DISABLED : {
            return *disabledSprite;
            break;
        }
        case UIbutton::State::ENABLED : {
            return *enabledSprite;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            return *highlightedSprite;
            break;
        }
        case UIbutton::State::SELECTED : {
            return *selectedSprite;
            break;
        }
    }
    Error("Não deveria chegar até aqui");
    return *disabledSprite; // Qualquer coisa, nao vai chegar aqui mesmo... Error faz o programa sair.
}

float UIimageButton::GetStateSpriteWidth(UIbutton::State state) const {
    return GetStateSprite(state).GetWidth();
}

float UIimageButton::GetStateSpriteHeight(UIbutton::State state) const {
    return GetStateSprite(state).GetHeight();
}

Vec2 UIimageButton::GetStateSpriteDimensions(UIbutton::State state) const {
    return Vec2(GetStateSprite(state).GetWidth(), GetStateSprite(state).GetHeight());
}

void UIimageButton::SetStateSpriteScale(UIbutton::State state, float scale) {
    switch(state) {
        case UIbutton::State::DISABLED : {
            disabledSprite->SetScale(scale);
            break;
        }
        case UIbutton::State::ENABLED : {
            enabledSprite->SetScale(scale);
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            highlightedSprite->SetScale(scale);
            break;
        }
        case UIbutton::State::SELECTED : {
            selectedSprite->SetScale(scale);
            break;
        }
    }
    if(state == actualState) {
        UpdateKernel();
    }
}

void UIimageButton::SetStateSpriteColorMultiplier(UIbutton::State state, Color color, SDL_BlendMode blendMode) {
    switch(state) {
        case UIbutton::State::DISABLED : {
            disabledSprite->colorMultiplier = color;
            disabledSprite->blendMode = blendMode;
            break;
        }
        case UIbutton::State::ENABLED : {
            enabledSprite->colorMultiplier = color;
            enabledSprite->blendMode = blendMode;
            break;
        }
        case UIbutton::State::HIGHLIGHTED : {
            highlightedSprite->colorMultiplier = color;
            highlightedSprite->blendMode = blendMode;
            break;
        }
        case UIbutton::State::SELECTED : {
            selectedSprite->colorMultiplier = color;
            selectedSprite->blendMode = blendMode;
            break;
        }
    }
}

bool UIimageButton::Is(std::string UItype) const {
    return "UIimageButton" == UItype || UIimage::Is(UItype) || UIbutton::Is(UItype);
}

void UIimageButton::UpdateKernel(void) {
    kernelSize = Vec2(sp->GetWidth(), sp->GetHeight());
}
