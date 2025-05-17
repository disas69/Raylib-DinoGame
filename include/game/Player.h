#pragma once

#include "framework/SpriteAnimation.h"
#include "framework/SpriteObject.h"

class AssetManager;

enum class PlayerState : char
{
    None = -1,
    Idle = 0,
    Run = 1,
    Jump = 2,
    Dead = 3,
};

class Player : public SpriteObject
{
public:
    explicit Player(raylib::Texture* texture, AssetManager* assetManager);

    void Update(float deltaTime);
    PlayerState GetState() const { return m_state; }
    void SetState(PlayerState state);

private:
    SpriteAnimation m_idleAnimation;
    SpriteAnimation m_runAnimation;

    PlayerState m_state = PlayerState::None;
};