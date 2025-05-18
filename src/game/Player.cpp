#include "game/Player.h"
#include "game/AssetManager.h"
#include <game/Settings.h>
#include <misc/easing.h>

Player::Player(raylib::Texture* texture, AssetManager* assetManager, GameSettings* gameSettings) : SpriteObject(texture),
    m_assetManager(assetManager), m_gameSettings(gameSettings)
{
    m_idleAnimation.AddFrame(texture);
    m_idleAnimation.SetFrameTime(0.1f);
    m_idleAnimation.SetLooping(false);

    m_runAnimation.AddFrame(assetManager->GetTexture("dino_run_1"));
    m_runAnimation.AddFrame(assetManager->GetTexture("dino_run_2"));
    m_runAnimation.SetFrameTime(0.1f);
    m_runAnimation.SetLooping(true);
}

void Player::Update(float deltaTime)
{
    if (!IsActive() || m_state == PlayerState::None || m_state == PlayerState::Idle || m_state == PlayerState::Dead)
    {
        return;
    }

    HandleInput();

    if (m_state == PlayerState::Jump)
    {
        UpdateJumpState();
    }

    if (m_isMoving)
    {
        const float speed = m_gameSettings->Player.MovementSpeed;
        SetPosition({GetPosition().x + speed * deltaTime, GetPosition().y});
    }
}

void Player::LateUpdate(float deltaTime)
{
    if (!IsActive())
    {
        return;
    }

    if (m_state == PlayerState::Idle || m_state == PlayerState::Jump)
    {
        m_idleAnimation.Update(deltaTime);
        SetTexture(m_idleAnimation.GetCurrentFrame());
    }
    else if (m_state == PlayerState::Run)
    {
        m_runAnimation.Update(deltaTime);
        SetTexture(m_runAnimation.GetCurrentFrame());
    }
}

void Player::SetState(PlayerState state)
{
    if (m_state != state)
    {
        m_state = state;

        if (m_state == PlayerState::Idle)
        {
            StopMoving();
            m_idleAnimation.Play();
        }
        else if (m_state == PlayerState::Jump)
        {
            m_idleAnimation.Play();
        }
        else if (m_state == PlayerState::Run)
        {
            StartMoving();
            m_runAnimation.Play();
        }
    }
}

void Player::Jump()
{
    if (m_state == PlayerState::Jump)
    {
        return;
    }

    m_jumpStartTime = GetTime();
    SetState(PlayerState::Jump);
}

void Player::HandleInput()
{
    if (IsKeyDown(KEY_SPACE))
    {
        Jump();
    }
}

void Player::UpdateJumpState()
{
    const float groundPos = m_gameSettings->ScreenHeight - GetHeight() - m_gameSettings->Player.GroundOffset;
    const float jumpDuration = m_gameSettings->Player.JumpDuration;

    const float elapsedTime = GetTime() - m_jumpStartTime;
    const float t = Clamp(elapsedTime / jumpDuration, 0.0f, 1.0f);
    if (t < 0.5f)
    {
        const float targetPos = groundPos - m_gameSettings->Player.JumpHeightMax;
        const float t1 = Remap(t, 0.0, 0.5f, 0.06f, 1.0f);
        const float lerpPos = Lerp(groundPos, targetPos, easeOutQuad(t1));
        SetPosition({GetPosition().x, lerpPos});
    }
    else if (t < 1.0f)
    {
        const float startPos = groundPos - m_gameSettings->Player.JumpHeightMax;
        const float t2 = Remap(t, 0.5f, 1.0f, 0.0f, 1.0f);
        const float lerpPos = Lerp(startPos, groundPos, easeInQuad(t2));
        SetPosition({GetPosition().x, lerpPos});
    }
    else
    {
        SetPosition({GetPosition().x, groundPos});
        SetState(PlayerState::Run);
    }
}
