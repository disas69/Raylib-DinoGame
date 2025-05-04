#pragma once

#include "framework/GameBase.h"
#include "framework/SpriteObject.h"
#include "Settings.h"
#include <vector>
#include <memory>

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

    std::unique_ptr<SpriteObject> m_player = nullptr;
    std::vector<std::unique_ptr<SpriteObject>> m_obstacles = {};
    std::vector<std::unique_ptr<SpriteObject>> m_grounds = {};

    GameSettings m_gameSettings = {};

    int m_screenWidth = 0;
    int m_screenHeight = 0;
    int m_groundIndex = 0;

    float m_playerStartOffset = 150.0f;
    float m_cameraXOffset = 400.f;
    float m_groundOffset = 75.f;
};