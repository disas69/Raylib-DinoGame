#include "game/Obstacle.h"

Obstacle::Obstacle(raylib::Texture* texture1, raylib::Texture* texture2) : SpriteObject(texture1)
{
    Initialize(texture1, texture2);
}

void Obstacle::Initialize(raylib::Texture* texture1, raylib::Texture* texture2)
{
    m_animation.ClearFrames();
    m_animation.AddFrame(texture1);
    if (texture2 != nullptr)
    {
        m_animation.AddFrame(texture2);
    }

    m_animation.SetFrameTime(0.1f);
    m_animation.SetLooping(true);
    m_animation.Play();
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

void Obstacle::SetupObstacle(std::unique_ptr<Obstacle>& obstacle, int offsetX, int screenHeight, GameSettings& gameSettings, AssetManager& assetManager)
{
    int positionY = screenHeight - obstacle->GetHeight() - gameSettings.Player.GroundOffset;

    switch (GetRandomValue(0, 6))
    {
        case 0:
            obstacle->Initialize(assetManager.GetTexture("cactus_small_1"));
        break;
        case 1:
            obstacle->Initialize(assetManager.GetTexture("cactus_small_2"));
        break;
        case 2:
            obstacle->Initialize(assetManager.GetTexture("cactus_small_3"));
        break;
        case 3:
            obstacle->Initialize(assetManager.GetTexture("cactus_large_1"));
        break;
        case 4:
            obstacle->Initialize(assetManager.GetTexture("cactus_large_2"));
        break;
        case 5:
            obstacle->Initialize(assetManager.GetTexture("cactus_large_3"));
        break;
        default:
            obstacle->Initialize(assetManager.GetTexture("bird_1"), assetManager.GetTexture("bird_2"));

            // Adjust position for bird
            switch (GetRandomValue(0, 2))
            {
                case 0:
                    // No adjustment
                break;
                case 1:
                    positionY -= obstacle->GetHeight();
                break;
                default:
                    positionY -= obstacle->GetHeight() / 2;
                    break;
            }
        break;
    }

    obstacle->SetPosition({static_cast<float>(offsetX), static_cast<float>(positionY)});
}