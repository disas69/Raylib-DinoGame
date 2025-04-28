#include "game/DinoGame.h"

void DinoGame::Load()
{
    m_dinoTexture = raylib::Texture("resources/sprites/Dino_Idle.png");
    m_obstacleTexture = raylib::Texture("resources/sprites/Cactus_Small_Single.png");
    m_groundTexture = raylib::Texture("resources/sprites/Ground.png");
}

void DinoGame::UpdateGame(float deltaTime)
{
}

void DinoGame::DrawGame(raylib::Window& window)
{
    window.BeginDrawing();
    window.ClearBackground(RAYWHITE);

    m_groundTexture.Draw(0, window.GetHeight() - m_groundTexture.GetHeight() - m_groundOffset);
    m_dinoTexture.Draw(100, window.GetHeight() - m_dinoTexture.GetHeight() - m_groundOffset);
    m_obstacleTexture.Draw(600, window.GetHeight() - m_obstacleTexture.GetHeight() - m_groundOffset);

    window.EndDrawing();
}

void DinoGame::Unload()
{
    m_dinoTexture.Unload();
    m_obstacleTexture.Unload();
    m_groundTexture.Unload();
}