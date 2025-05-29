#pragma once

#include "framework/SpriteObject.h"
#include "framework/SpriteAnimation.h"

class Obstacle : public SpriteObject
{
public:
    explicit Obstacle(raylib::Texture* texture1, raylib::Texture* texture2);

    void LateUpdate(float deltaTime);

private:
    SpriteAnimation m_animation;
};