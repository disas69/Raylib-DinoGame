#include "game/Game.h"

namespace GameConfig
{
int OBSTACLE_POOL_SIZE = 10;
int GROUND_POOL_SIZE = 2;
}

void Game::Initialize()
{
    // Load resources
    m_assetManager.LoadAssets();

    // TODO: Load json and apply settings
    m_gameSettings = GameSettings();
    m_gameSettings.ScreenWidth = m_screenWidth;
    m_gameSettings.ScreenHeight = m_screenHeight;

    // Create game objects
    m_camera.SetOffset({m_screenWidth / 2.0f - m_gameSettings.CameraXOffset, m_screenHeight / 2.0f - m_gameSettings.CameraYOffset});
    m_camera.SetRotation(0.f);
    m_camera.SetZoom(0.8f);

    m_player = std::make_unique<Player>(m_assetManager.GetTexture("dino"), &m_assetManager, &m_gameSettings);
    m_player->SetPosition({m_gameSettings.Player.StartOffset, m_screenHeight - m_player->GetHeight() - m_gameSettings.Player.GroundOffset});
    m_player->SetState(PlayerState::Idle);

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
        m_grounds[i]->SetPosition({i * m_grounds[i]->GetRectangle().width, m_screenHeight - m_grounds[i]->GetHeight() - m_gameSettings.Player.GroundOffset});
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
    // Start the game
    if (IsKeyDown(KEY_SPACE) && m_player->GetState() == PlayerState::Idle)
    {
        m_player->SetState(PlayerState::Run);
    }

    // Update game objects
    m_player->Update(deltaTime);

    Vector2 playerPos = m_player->GetPosition();
    auto& currentGround = m_grounds[m_groundIndex];
    if (currentGround->GetPosition().x < playerPos.x - m_gameSettings.Player.StartOffset)
    {
        m_groundIndex = (m_groundIndex + 1) % GameConfig::GROUND_POOL_SIZE;
        auto& nextGround = m_grounds[m_groundIndex];
        nextGround->SetPosition({currentGround->GetPosition().x + currentGround->GetRectangle().width, m_screenHeight - nextGround->GetHeight() - m_gameSettings.Player.GroundOffset});
    }

    // TODO: Activate and update obstacles position based on total distance passed
    // TODO: Deactivate passed obstacles

    // TODO: Check collisions

    // Update animations
    m_player->LateUpdate(deltaTime);

    // TODO: Update score

    // Update camera
    const float groundPos = m_screenHeight - m_player->GetHeight() - m_gameSettings.Player.GroundOffset;
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
