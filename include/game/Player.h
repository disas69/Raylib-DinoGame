#pragma once

#include "framework/SpriteAnimation.h"
#include "framework/SpriteObject.h"

struct GameSettings;
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
    explicit Player(raylib::Texture* texture, AssetManager* assetManager, GameSettings* gameSettings);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);

    PlayerState GetState() const { return m_state; }
    void SetState(PlayerState state);

private:
    SpriteAnimation m_idleAnimation;
    SpriteAnimation m_runAnimation;

    AssetManager* m_assetManager = nullptr;
    GameSettings* m_gameSettings = nullptr;

    PlayerState m_state = PlayerState::None;
    float m_jumpStartTime = 0.0f;

    void HandleInput();
    void UpdateJumpState();
};
