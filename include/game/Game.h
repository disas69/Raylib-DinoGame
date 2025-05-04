#pragma once

#include "framework/GameBase.h"
#include "framework/SpriteObject.h"

class Game : public framework::GameBase
{
public:
    Game() { Initialize(); }
    ~Game() override { Dispose(); }

    void UpdateGame(float deltaTime) override;
    void DrawGame(raylib::Window& window) override;

private:
    void Initialize();
    void Dispose();

    raylib::Camera2D m_camera;

    raylib::Texture m_dinoTexture;
    raylib::Texture m_obstacleTexture;
    raylib::Texture m_groundTexture;

    SpriteObject* m_player = nullptr;
    SpriteObject* m_obstacle = nullptr;
    SpriteObject* m_ground = nullptr;

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    float m_cameraXOffset = 350.f;
    float m_groundOffset = 75.f;
};