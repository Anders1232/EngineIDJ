#ifndef UITEXTBUTTON_H
#define UITEXTBUTTON_H

#include "UItext.h"
#include "UIbutton.h"
#include "Rect.h"

#include <string>

class UItextButton : public UItext, public UIbutton {
  public:
    UItextButton
        (
			string fontFile,
			int fontSize,
			UItext::TextStyle style,
			SDL_Color color,
			string text,
			UIelement::BehaviorType behavior = UIelement::BehaviorType::FIT,
			bool isStrobing = false
		);
    void ConfigColors(SDL_Color disabled, SDL_Color enabled, SDL_Color highlighted);
    void SetUIbuttonState(UIbutton::State newState);
    void SetStateColor(UIbutton::State state, SDL_Color color);
    SDL_Color GetStateColor(UIbutton::State state) const ;
    void Update(float dt, Rect parentCanvas);
    void Render(bool debugRender = false) const ;
    bool Is(std::string UItype) const ;
  private:
    SDL_Color disabledColor;
    SDL_Color enabledColor;
    SDL_Color highlightedColor;
};

#endif // UITEXTBUTTON_H
