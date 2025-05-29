#pragma once

#include "AssetManager.h"
#include "Settings.h"
#include "framework/SpriteObject.h"
#include "framework/SpriteAnimation.h"
#include <memory>

class Obstacle : public SpriteObject
{
public:
    explicit Obstacle(raylib::Texture* texture1, raylib::Texture* texture2 = nullptr);

    void Initialize(raylib::Texture* texture1, raylib::Texture* texture2 = nullptr);
    void LateUpdate(float deltaTime);

    static void SetupObstacle(std::unique_ptr<Obstacle>& obstacle, int offsetX, int screenHeight, GameSettings& gameSettings, AssetManager& assetManager);

private:
    SpriteAnimation m_animation;
};