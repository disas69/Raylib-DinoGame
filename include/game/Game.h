#pragma once

#include "AssetManager.h"
#include "framework/GameBase.h"
#include "framework/SpriteObject.h"
#include "game/Player.h"
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

    void HandleInput();
    void UpdatePlayerJump();

    AssetManager m_assetManager;
    raylib::Camera2D m_camera;

    std::unique_ptr<Player> m_player = nullptr;
    std::vector<std::unique_ptr<SpriteObject>> m_obstacles = {};
    std::vector<std::unique_ptr<SpriteObject>> m_grounds = {};

    GameSettings m_gameSettings = {};

    int m_screenWidth = 0;
    int m_screenHeight = 0;
    int m_groundIndex = 0;

    float m_playerStartOffset = 150.0f;
    float m_cameraXOffset = 380.0f;
    float m_cameraYOffset = -30.0f;
    float m_groundOffset = 50.0f;

    float m_jumpStartTime = 0.0f;
    bool m_jumping = false;
};