#include "game/Game.h"

void Game::Initialize()
{
    // Init static variables
    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();

    // Load config and apply settings

    // Init components
    m_camera.SetOffset({m_screenWidth / 2.0f - m_cameraXOffset, m_screenHeight / 2.0f});
    m_camera.SetRotation(0.f);
    m_camera.SetZoom(1.0f);

    // Load resources
    m_dinoTexture = raylib::Texture("resources/sprites/Dino_Idle.png");
    m_obstacleTexture = raylib::Texture("resources/sprites/Cactus_Small_Single.png");
    m_groundTexture = raylib::Texture("resources/sprites/Ground.png");

    // Create actors
    m_player = new SpriteObject(&m_dinoTexture);
    m_player->SetPosition({100, m_screenHeight - m_dinoTexture.GetHeight() - m_groundOffset});

    m_obstacle = new SpriteObject(&m_obstacleTexture);
    m_obstacle->SetPosition({600, m_screenHeight - m_obstacleTexture.GetHeight() - m_groundOffset});

    m_ground = new SpriteObject(&m_groundTexture);
    m_ground->SetPosition({0, m_screenHeight - m_groundTexture.GetHeight() - m_groundOffset});

    // Load score from file

    // Init game state

    // Init UI and open start screen
}

void Game::UpdateGame(float deltaTime)
{
    // Handle input
    if (IsKeyDown(KEY_RIGHT))
    {
        m_player->SetPosition({m_player->GetPosition().x + 150 * deltaTime, m_player->GetPosition().y});
    }
    else if (IsKeyDown(KEY_LEFT))
    {
        m_player->SetPosition({m_player->GetPosition().x - 150 * deltaTime, m_player->GetPosition().y});
    }

    // Update player actor, update animations

    // Update camera
    m_camera.SetTarget(m_player->GetPosition());

    // Update obstacles spawner

    // Check collisions

    // Update game state
}

void Game::DrawGame(raylib::Window& window)
{
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);

    m_camera.BeginMode();

    // Draw ground
    m_ground->Draw();

    // Draw obstacles
    m_obstacle->Draw();

    // Draw player
    m_player->Draw();

    m_camera.EndMode();

    // Draw UI

    window.EndDrawing();
}

void Game::Dispose()
{
    // Save score to file

    // Unload resources
    m_dinoTexture.Unload();
    m_obstacleTexture.Unload();
    m_groundTexture.Unload();
}