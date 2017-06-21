#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Sprite.h"
#include "Rect.h"
#include "Vec2.h"

#include <string>

class UIelement {
  public:
    enum BehaviorType {
        FIT,
        FILL,
        STRETCH
    };
    void SetAnchors(Vec2 min, Vec2 max);
    void SetOffsets(Vec2 min, Vec2 max);
    void SetBehavior(BehaviorType type);
    virtual void Update(float dt, Rect parentCanvas);
    virtual void Render(bool debugRender = false) const;
    virtual bool Is(std::string UItype) const;
    Rect GetBoundingBox(void) const;
    Rect ComputeBoundingbox(Rect parentCanvas);
    Rect ComputeBox();
    operator Rect() const;
  protected:
    UIelement(BehaviorType behavior = BehaviorType::STRETCH);
    Rect boundingBox;
    Rect box;
    Vec2 kernelSize;
  private:
    Rect anchors; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    Rect offsets; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    BehaviorType behavior;
};

#endif // UIELEMENT_H
