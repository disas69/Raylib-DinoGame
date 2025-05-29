#include "game/Game.h"

void Game::Initialize()
{
    // Load all resources
    m_assetManager.LoadAssets();
    LoadData();

    // Setup camera
    m_camera.SetOffset({m_screenWidth / 2.0f - m_gameSettings.CameraXOffset, m_screenHeight / 2.0f - m_gameSettings.CameraYOffset});
    m_camera.SetRotation(0.f);
    m_camera.SetZoom(0.8f);

    // Create game objects
    m_player = std::make_unique<Player>(m_assetManager.GetTexture("dino"), &m_assetManager, &m_gameSettings);
    m_player->SetActive(false);

    m_obstacles = std::vector<std::unique_ptr<Obstacle>>(OBSTACLE_POOL_SIZE);
    for (int i = 0; i < OBSTACLE_POOL_SIZE; ++i)
    {
        m_obstacles[i] = std::make_unique<Obstacle>(m_assetManager.GetTexture("cactus_small_1"));
        m_obstacles[i]->SetActive(false);
    }

    m_grounds = std::vector<std::unique_ptr<SpriteObject>>(GROUND_POOL_SIZE);
    for (int i = 0; i < GROUND_POOL_SIZE; ++i)
    {
        m_grounds[i] = std::make_unique<SpriteObject>(m_assetManager.GetTexture("ground"));
        m_grounds[i]->SetActive(false);
    }

    m_uiManager.Initialize(m_assetManager.GetFont("main"), m_assetManager.GetTexture("retry"), m_gameSettings.ScreenWidth, m_gameSettings.ScreenHeight);

    SetGameState(GameState::Start);
}

void Game::Dispose()
{
    SaveData();

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

        for (int i = 0; i < m_grounds.size(); ++i)
        {
            m_grounds[i]->SetPosition({i * m_grounds[i]->GetRectangle().width, m_screenHeight - m_grounds[i]->GetHeight() - m_gameSettings.Player.GroundOffset});
            m_grounds[i]->SetActive(true);
        }

        m_obstacleOffset = m_gameSettings.Obstacle.Offset;
        const int obstacleMinDistance = m_gameSettings.Obstacle.MinSpawnDistance;
        const int obstacleMaxDistance = m_gameSettings.Obstacle.MaxSpawnDistance;

        for (auto& obstacle : m_obstacles)
        {
            m_obstacleOffset += GetRandomValue(obstacleMinDistance, obstacleMaxDistance);
            Obstacle::SetupObstacle(obstacle, m_obstacleOffset, m_screenHeight, m_gameSettings, m_assetManager);
            obstacle->SetActive(true);
        }

        m_uiManager.Reset();
    }
    else if (m_gameState == GameState::Play)
    {
        m_player->Jump();
        m_uiManager.PlayStartAnimation();
    }
    else if (m_gameState == GameState::GameOver)
    {
        m_player->SetState(PlayerState::Dead);
    }
}

void Game::LoadData()
{
    char* saveData = LoadFileText("save_data.txt");
    if (saveData != nullptr)
    {
        std::string dataStr(saveData);
        UnloadFileText(saveData);

        // Parse the data
        size_t pos = dataStr.find("BestScore:");
        if (pos != std::string::npos)
        {
            pos += 10;
            m_bestScore = std::stoi(dataStr.substr(pos));
        }
    }
    else
    {
        m_bestScore = 0;
    }
}

void Game::SaveData()
{
    const char* saveData = TextFormat("BestScore:%d", m_bestScore);
    SaveFileText("save_data.txt", const_cast<char*>(saveData));
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
            m_groundIndex = (m_groundIndex + 1) % GROUND_POOL_SIZE;
            std::unique_ptr<SpriteObject>& nextGround = m_grounds[m_groundIndex];
            nextGround->SetPosition({currentGround->GetPosition().x + currentGround->GetRectangle().width, m_screenHeight - nextGround->GetHeight() - m_gameSettings.Player.GroundOffset});
        }

        for (const auto& obstacle : m_obstacles)
        {
            if (obstacle->IsActive())
            {
                if (CheckCollisionRecs(m_player->GetRectangle(), obstacle->GetRectangle()))
                {
                    SetGameState(GameState::GameOver);
                    break;
                }
            }
        }

        for (auto& obstacle : m_obstacles)
        {
            if (obstacle->IsActive())
            {
                if (obstacle->GetPosition().x <= playerPos.x - m_gameSettings.Player.StartOffset - 100)
                {
                    const int obstacleMinDistance = m_gameSettings.Obstacle.MinSpawnDistance;
                    const int obstacleMaxDistance = m_gameSettings.Obstacle.MaxSpawnDistance;

                    m_obstacleOffset += GetRandomValue(obstacleMinDistance, obstacleMaxDistance);
                    Obstacle::SetupObstacle(obstacle, m_obstacleOffset, m_screenHeight, m_gameSettings, m_assetManager);
                }
            }
        }

        // Update score
        m_score = static_cast<int>((playerPos.x - m_gameSettings.Player.StartOffset) * 0.015f);
        if (m_score > m_bestScore)
        {
            m_bestScore = m_score;
        }

        // Update animations
        m_player->LateUpdate(deltaTime);

        for (const auto& obstacle : m_obstacles)
        {
            obstacle->LateUpdate(deltaTime);
        }
    }
    else if (m_gameState == GameState::GameOver)
    {
        // Restart the game
        if (IsKeyPressed(KEY_SPACE) || m_uiManager.ShouldRestart())
        {
            SetGameState(GameState::Start);
            SetGameState(GameState::Play);
        }
    }

    // Update camera
    const float groundPos = m_screenHeight - m_player->GetHeight() - m_gameSettings.Player.GroundOffset;
    const Vector2 camFollowPos = {m_player->GetPosition().x, groundPos};
    m_camera.SetTarget(camFollowPos);

    // Update UI
    m_uiManager.Update(deltaTime);
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
