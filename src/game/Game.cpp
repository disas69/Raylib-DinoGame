#include "game/Game.h"

namespace GameConfig
{
int OBSTACLE_POOL_SIZE = 10;
int GROUND_POOL_SIZE = 2;
}

void Game::Initialize()
{
    // Load all resources
    m_assetManager.LoadAssets();

    // Setup camera
    m_camera.SetOffset({m_screenWidth / 2.0f - m_gameSettings.CameraXOffset, m_screenHeight / 2.0f - m_gameSettings.CameraYOffset});
    m_camera.SetRotation(0.f);
    m_camera.SetZoom(0.8f);

    // Create game objects
    m_player = std::make_unique<Player>(m_assetManager.GetTexture("dino"), &m_assetManager, &m_gameSettings);
    m_player->SetActive(false);

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
        m_grounds[i]->SetActive(false);
    }

    m_uiManager.Initialize(m_assetManager.GetFont("main"), m_gameSettings.ScreenWidth, m_gameSettings.ScreenHeight);

    // TODO: Load best score from json

    SetGameState(GameState::Start);
}

void Game::Dispose()
{
    // TODO: Save best score to json

    // Unload all resources
    m_assetManager.UnloadAssets();
}

void Game::SetGameState(GameState state)
{
    if (m_gameState == state)
    {
        return;
    }

    m_gameState = state;

    if (m_gameState == GameState::Start)
    {
        m_score = 0;

        m_player->SetActive(true);
        m_player->SetState(PlayerState::Idle);
        m_player->SetPosition({m_gameSettings.Player.StartOffset, m_screenHeight - m_player->GetHeight() - m_gameSettings.Player.GroundOffset});

        for (int i = 0; i < GameConfig::GROUND_POOL_SIZE; ++i)
        {
            m_grounds[i]->SetActive(true);
            m_grounds[i]->SetPosition({i * m_grounds[i]->GetRectangle().width, m_screenHeight - m_grounds[i]->GetHeight() - m_gameSettings.Player.GroundOffset});
        }
    }
    else if (m_gameState == GameState::Play)
    {
        // TODO: Start game, show game screen
        m_player->Jump();
    }
    else if (m_gameState == GameState::GameOver)
    {
        // TODO: Stop game, show game over screen
        m_player->SetState(PlayerState::Dead);
    }
}

void Game::UpdateGame(float deltaTime)
{
    if (m_gameState == GameState::Start)
    {
        // Start the game
        if (IsKeyDown(KEY_SPACE))
        {
            SetGameState(GameState::Play);
        }
    }
    else if (m_gameState == GameState::Play)
    {
        // Update game objects
        m_player->Update(deltaTime);

        Vector2 playerPos = m_player->GetPosition();
        std::unique_ptr<SpriteObject>& currentGround = m_grounds[m_groundIndex];
        if (currentGround->GetPosition().x < playerPos.x - m_gameSettings.Player.StartOffset)
        {
            m_groundIndex = (m_groundIndex + 1) % GameConfig::GROUND_POOL_SIZE;
            std::unique_ptr<SpriteObject>& nextGround = m_grounds[m_groundIndex];
            nextGround->SetPosition({currentGround->GetPosition().x + currentGround->GetRectangle().width, m_screenHeight - nextGround->GetHeight() - m_gameSettings.Player.GroundOffset});
        }

        // TODO: Activate and update obstacles position based on total distance passed
        // TODO: Update score
        // TODO: Deactivate passed obstacles
        // TODO: Check collisions

        // Update animations
        m_player->LateUpdate(deltaTime);
    }
    else if (m_gameState == GameState::GameOver)
    {
        // Restart the game
        if (IsKeyDown(KEY_SPACE))
        {
            SetGameState(GameState::Start);
            SetGameState(GameState::Play);
        }
    }

    // Update camera
    const float groundPos = m_screenHeight - m_player->GetHeight() - m_gameSettings.Player.GroundOffset;
    const Vector2 camFollowPos = {m_player->GetPosition().x, groundPos};
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

    // Draw UI
    m_uiManager.Draw(m_gameState, m_score, m_bestScore);

    window.EndDrawing();
}
