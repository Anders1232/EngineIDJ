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
    UIelement(BehaviorType behavior = BehaviorType::STRETCH);
    void SetAnchors(Vec2 min, Vec2 max);
    void SetOffsets(Vec2 min, Vec2 max);
    void SetBehavior(BehaviorType type);
    virtual void SetKernelSize(Vec2 kernelSize) = 0;
    virtual void Update(float dt, Rect parentCanvas);
    virtual void Render(bool debugRender = false) const;
    Rect ComputeBoundingbox(Rect parentCanvas);
    Rect ComputeBox();
    operator Rect();
  protected:
    Rect boundingBox;
    Rect box;
    Vec2 kernelSize;
  private:
    Rect anchors; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    Rect offsets; // Coordenadas W e H sao absolutas, e nao relativas como comumente usadas em Rects
    BehaviorType behavior;
};

#endif // UIELEMENT_H
