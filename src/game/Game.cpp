#include "game/Game.h"
#include "misc/easing.h"

namespace GameConfig
{
int OBSTACLE_POOL_SIZE = 10;
int GROUND_POOL_SIZE = 2;
}

void Game::Initialize()
{
    // Load resources
    m_assetManager.LoadAssets();

    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();

    // TODO: Load json and apply settings
    m_gameSettings = GameSettings();

    // Create game objects
    m_camera.SetOffset({m_screenWidth / 2.0f - m_cameraXOffset, m_screenHeight / 2.0f - m_cameraYOffset});
    m_camera.SetRotation(0.f);
    m_camera.SetZoom(0.8f);

    m_player = std::make_unique<Player>(m_assetManager.GetTexture("dino"), &m_assetManager);
    m_player->SetPosition({m_playerStartOffset, m_screenHeight - m_player->GetHeight() - m_groundOffset});
    m_player->SetState(PlayerState::Run);

    m_obstacles = std::vector<std::unique_ptr<SpriteObject>>(GameConfig::OBSTACLE_POOL_SIZE);
    for (int i = 0; i < GameConfig::OBSTACLE_POOL_SIZE; ++i)
    {
        m_obstacles[i] = std::make_unique<SpriteObject>(m_assetManager.GetTexture("cactus"));
        m_obstacles[i]->SetActive(false);
    }

    m_grounds = std::vector<std::unique_ptr<SpriteObject>>(GameConfig::GROUND_POOL_SIZE);
    for (int i = 0; i < GameConfig::GROUND_POOL_SIZE; ++i)
    {
        m_grounds[i] = std::make_unique<SpriteObject>(m_assetManager.GetTexture("ground"));
        m_grounds[i]->SetPosition({i * m_grounds[i]->GetRectangle().width, m_screenHeight - m_grounds[i]->GetHeight() - m_groundOffset});
    }

    // TODO: Load best score from json
    // TODO: Init game state
    // TODO: Init UI and open start screen
}

void Game::Dispose()
{
    // TODO: Save best score to json
    // TODO: Destroy objects

    // Unload resources
    m_assetManager.UnloadAssets();
}

void Game::UpdateGame(float deltaTime)
{
    HandleInput();
    UpdatePlayerJump();

    // Update game objects
    const float speed = m_gameSettings.PlayerSettings.MovementSpeed;
    m_player->SetPosition({m_player->GetPosition().x + speed * deltaTime, m_player->GetPosition().y});

    Vector2 playerPos = m_player->GetPosition();
    auto& currentGround = m_grounds[m_groundIndex];
    if (currentGround->GetPosition().x < playerPos.x - m_playerStartOffset)
    {
        m_groundIndex = (m_groundIndex + 1) % GameConfig::GROUND_POOL_SIZE;
        auto& nextGround = m_grounds[m_groundIndex];
        nextGround->SetPosition({currentGround->GetPosition().x + currentGround->GetRectangle().width, m_screenHeight - nextGround->GetHeight() - m_groundOffset});
    }

    // TODO: Activate and update obstacles position based on total distance passed
    // TODO: Deactivate passed obstacles

    // TODO: Check collisions

    // Update states and animations
    m_player->Update(deltaTime);

    // TODO: Update score

    // Update camera
    const float groundPos = m_screenHeight - m_player->GetHeight() - m_groundOffset;
    const Vector2 camFollowPos = {playerPos.x, groundPos};
    m_camera.SetTarget(camFollowPos);
}

void Game::DrawGame(raylib::Window& window)
{
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);

    // Draw game objects
    m_camera.BeginMode();
    for (const auto& ground : m_grounds)
    {
        ground->Draw();
    }

    for (const auto& obstacle : m_obstacles)
    {
        obstacle->Draw();
    }

    m_player->Draw();
    m_camera.EndMode();

    // TODO: Draw UI

    window.EndDrawing();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_SPACE))
    {
        if (m_jumping)
        {
            return;
        }

        m_player->SetState(PlayerState::Jump);
        m_jumpStartTime = GetTime();
        m_jumping = true;
    }
}

void Game::UpdatePlayerJump()
{
    if (!m_jumping)
    {
        return;
    }

    const float groundPos = m_screenHeight - m_player->GetHeight() - m_groundOffset;
    const float jumpDuration = m_gameSettings.PlayerSettings.JumpDuration;

    const float elapsedTime = GetTime() - m_jumpStartTime;
    const float t = Clamp(elapsedTime / jumpDuration, 0.0f, 1.0f);
    if (t < 0.5f)
    {
        const float targetPos = groundPos - m_gameSettings.PlayerSettings.JumpHeightMax;
        const float t1 = Remap(t, 0.0, 0.5f, 0.06f, 1.0f);
        const float lerpPos = Lerp(groundPos, targetPos, easeOutQuad(t1));
        m_player->SetPosition({m_player->GetPosition().x, lerpPos});
    }
    else if (t < 1.0f)
    {
        const float startPos = groundPos - m_gameSettings.PlayerSettings.JumpHeightMax;
        const float t2 = Remap(t, 0.5f, 1.0f, 0.0f, 1.0f);
        const float lerpPos = Lerp(startPos, groundPos, easeInQuad(t2));
        m_player->SetPosition({m_player->GetPosition().x, lerpPos});
    }
    else
    {
        m_player->SetState(PlayerState::Run);
        m_player->SetPosition({m_player->GetPosition().x, groundPos});
        m_jumping = false;
    }
}
