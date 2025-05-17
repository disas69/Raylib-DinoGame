#include "game/Player.h"
#include "game/AssetManager.h"

Player::Player(raylib::Texture* texture, AssetManager* assetManager) : SpriteObject(texture)
{
    m_idleAnimation.AddFrame(texture);
    m_idleAnimation.SetFrameTime(1.0f);
    m_idleAnimation.SetLooping(false);

    m_runAnimation.AddFrame(assetManager->GetTexture("dino_run_1"));
    m_runAnimation.AddFrame(assetManager->GetTexture("dino_run_2"));
    m_runAnimation.SetFrameTime(0.1f);
    m_runAnimation.SetLooping(true);
}

void Player::Update(float deltaTime)
{
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
        if (m_state == PlayerState::Idle || m_state == PlayerState::Jump)
        {
            m_idleAnimation.Play();
        }
        else if (m_state == PlayerState::Run)
        {
            m_runAnimation.Play();
        }
    }
}