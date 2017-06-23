#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"
#include "TileMap.h"
#include "Sprite.h"
#include "Rect.h"
#include "Camera.h"
#include "Vec2.h"

#include <string>

class Obstacle : public GameObject{
    public:
        Obstacle(std::string path, Vec2 position);
        void Update(float dt);
        void Render(void);
        void RequestDelete(void);
        void NotifyCollision(GameObject &object);
        Rect GetWorldRenderedRect(void) const;
        bool Is(string type);
    private:
        Sprite sp;
};

#endif // OBSTACLE_H