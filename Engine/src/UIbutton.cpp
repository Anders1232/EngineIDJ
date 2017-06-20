#include "UIbutton.h"

UIbutton::UIbutton(UIelement::BehaviorType behavior, UIbutton::State initialState)
        : UIelement(behavior)
        , actualState(initialState)
        , elements{nullptr} {}

const UIelement* UIbutton::GetUIelement(UIbutton::State whichElement) const {
    int index = static_cast<int>(whichElement);
    return elements[index];
}

void UIbutton::SetUIelement(UIbutton::State whichElement, UIelement* element) {
    int index = static_cast<int>(whichElement);
    elements[index] = element;
}

void UIbutton::Update(float dt, Rect parentCanvas) {
    UIelement::Update(dt, parentCanvas);
    for(int i = 0; i < 4; i++) {
        if(nullptr != elements[i]) {
            elements[i]->Update(dt, box);
        }
    }
}

void UIbutton::Render(bool debugRender) const {
    UIelement::Render(debugRender);
    const UIelement* toRender = GetUIelement(actualState);
    if (nullptr != toRender) {
        toRender->Render(debugRender);
    }
}

void UIbutton::SetKernelSize(Vec2 kernelSize) { // É para ser ignorado mesmo
    for(int i = 0; i < 4; i++) {
        if(nullptr != elements[i]) {
            elements[i]->SetKernelSize(kernelSize);
        }
    }
}

bool UIbutton::Is(std::string UItype) const {
    return "UIbutton" == UItype;
}
