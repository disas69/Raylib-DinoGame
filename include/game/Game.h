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

    AssetManager m_assetManager;
    GameSettings m_gameSettings;

    raylib::Camera2D m_camera;
    std::unique_ptr<Player> m_player = nullptr;
    std::vector<std::unique_ptr<SpriteObject>> m_obstacles = {};
    std::vector<std::unique_ptr<SpriteObject>> m_grounds = {};

    int m_groundIndex = 0;
};