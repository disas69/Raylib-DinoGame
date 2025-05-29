#include "game/Obstacle.h"

Obstacle::Obstacle(raylib::Texture* texture1, raylib::Texture* texture2) : SpriteObject(texture1)
{
    m_animation.AddFrame(texture1);
    if (texture2 != nullptr)
    {
        m_animation.AddFrame(texture2);
    }
    m_animation.SetFrameTime(0.1f);
    m_animation.SetLooping(true);
}

void Obstacle::LateUpdate(float deltaTime)
{
    if (!IsActive())
    {
        return;
    }

    m_animation.Update(deltaTime);
    SetTexture(m_animation.GetCurrentFrame());
}