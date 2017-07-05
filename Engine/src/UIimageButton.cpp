#include "UIimageButton.h"

#include "Error.h"

UIimageButton::UIimageButton(UIbutton::State initialState, UIelement::BehaviorType behavior)
				: UIimage(behavior)
				, UIbutton(initialState, false)
				, disabledSprite(nullptr)
				, enabledSprite(nullptr)
				, highlightedSprite(nullptr)
				, pressedSprite(nullptr) {}

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
	if(nullptr != pressedSprite) {
		delete pressedSprite;
	}
}

void UIimageButton::Update(float dt, Rect parentCanvas) {
	UIimage::Update(dt, parentCanvas);
	UIbutton::Update(dt, INPUT_MANAGER.GetMousePos().IsInRect( interactOnBoundingBox ? boundingBox : box));
}

void UIimageButton::SetUIbuttonState(UIbutton::State newState) {
	if(newState == actualState) return;
	switch(newState) {
		case UIbutton::State::DISABLED : {
			if(nullptr != disabledSprite) {
				sp = disabledSprite;
			} else {
				REPORT_DEBUG2(true, " Sprite Disabled não configurada.");
			}
			break;
		}
		case UIbutton::State::ENABLED : {
			if(nullptr != enabledSprite) {
				sp = enabledSprite;
			} else {
				REPORT_DEBUG2(true, " Sprite Enabled não configurada.");
			}
			break;
		}
		case UIbutton::State::HIGHLIGHTED : {
			if(nullptr != highlightedSprite) {
				sp = highlightedSprite;
			} else {
				REPORT_DEBUG2(true, " Sprite Highlighted não configurada.");
			}
			break;
		}
		case UIbutton::State::PRESSED : {
			if(nullptr != pressedSprite) {
				sp = pressedSprite;
			} else {
				REPORT_DEBUG2(true, " Sprite Pressed não configurada.");
			}
			break;
		}
	}
	UpdateKernel();
	UIbutton::SetUIbuttonState(newState);
}

void UIimageButton::SetStateSprite(UIbutton::State state, Sprite* sprite) {
	switch(state) {
		case UIbutton::State::DISABLED : {
			if(nullptr != disabledSprite) {
				delete disabledSprite;
			}
			disabledSprite = sprite;
			break;
		}
		case UIbutton::State::ENABLED : {
			if(nullptr != enabledSprite) {
				delete enabledSprite;
			}
			enabledSprite = sprite;
			break;
		}
		case UIbutton::State::HIGHLIGHTED : {
			if(nullptr != highlightedSprite) {
				delete highlightedSprite;
			}
			highlightedSprite = sprite;
			break;
		}
		case UIbutton::State::PRESSED : {
			if(nullptr != pressedSprite) {
				delete pressedSprite;
			}
			pressedSprite = sprite;
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
			ASSERT(nullptr != disabledSprite);
			return *disabledSprite;
			break;
		}
		case UIbutton::State::ENABLED : {
			ASSERT(nullptr != enabledSprite);
			return *enabledSprite;
			break;
		}
		case UIbutton::State::HIGHLIGHTED : {
			ASSERT(nullptr != highlightedSprite);
			return *highlightedSprite;
			break;
		}
		case UIbutton::State::PRESSED : {
			ASSERT(nullptr != pressedSprite);
			return *pressedSprite;
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
			if (nullptr != disabledSprite) {
				disabledSprite->SetScale(scale);
			} else {
				REPORT_DEBUG2(true, " Sprite Disabled não configurada.");
			}
			break;
		}
		case UIbutton::State::ENABLED : {
			if (nullptr != enabledSprite) {
				enabledSprite->SetScale(scale);
			} else {
				REPORT_DEBUG2(true, " Sprite Enabled não configurada.");
			}
			break;
		}
		case UIbutton::State::HIGHLIGHTED : {
			if (nullptr != highlightedSprite) {
				highlightedSprite->SetScale(scale);
			} else {
				REPORT_DEBUG2(true, " Sprite Highlighted não configurada.");
			}
			break;
		}
		case UIbutton::State::PRESSED : {
			if (nullptr != pressedSprite) {
				pressedSprite->SetScale(scale);
			} else {
				REPORT_DEBUG2(true, " Sprite Pressed não configurada.");
			}
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
			if(nullptr != disabledSprite) {
				disabledSprite->colorMultiplier = color;
				disabledSprite->blendMode = blendMode;
			} else {
				REPORT_DEBUG2(true, " Sprite Disabled não configurada.");
			}
			break;
		}
		case UIbutton::State::ENABLED : {
			if(nullptr != enabledSprite) {
				enabledSprite->colorMultiplier = color;
				enabledSprite->blendMode = blendMode;
			} else {
				REPORT_DEBUG2(true, " Sprite Enabled não configurada.");
			}
			break;
		}
		case UIbutton::State::HIGHLIGHTED : {
			if(nullptr != highlightedSprite) {
				highlightedSprite->colorMultiplier = color;
				highlightedSprite->blendMode = blendMode;
			} else {
				REPORT_DEBUG2(true, " Sprite Highlighted não configurada.");
			}
			break;
		}
		case UIbutton::State::PRESSED : {
			if(nullptr != pressedSprite) {
				pressedSprite->colorMultiplier = color;
				pressedSprite->blendMode = blendMode;
			} else {
				REPORT_DEBUG2(true, " Sprite Pressed não configurada.");
			}
			break;
		}
	}
}

bool UIimageButton::Is(std::string UItype) const {
	return "UIimageButton" == UItype || UIimage::Is(UItype) || UIbutton::Is(UItype);
}

void UIimageButton::UpdateKernel(void) {
	if(nullptr != sp) {
		kernelSize = Vec2(sp->GetWidth(), sp->GetHeight());
	}
}
