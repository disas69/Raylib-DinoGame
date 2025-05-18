#pragma once

#include "AssetManager.h"
#include "framework/GameBase.h"
#include "framework/SpriteObject.h"
#include "game/Player.h"
#include "Settings.h"
#include <vector>
#include <memory>

enum class GameState : char
{
    None = -1,
    Start = 0,
    Play = 1,
    GameOver = 2,
};

class Game : public framework::GameBase
{
public:
    explicit Game(const GameSettings& gameSettings) : m_gameSettings(gameSettings) { Initialize(); }
    ~Game() override { Dispose(); }

    void UpdateGame(float deltaTime) override;
    void DrawGame(raylib::Window& window) override;

private:
    GameSettings m_gameSettings;
    AssetManager m_assetManager;

    raylib::Camera2D m_camera;
    std::unique_ptr<Player> m_player = nullptr;
    std::vector<std::unique_ptr<SpriteObject>> m_obstacles = {};
    std::vector<std::unique_ptr<SpriteObject>> m_grounds = {};

    GameState m_gameState = GameState::None;
    int m_groundIndex = 0;

    void Initialize();
    void Dispose();
    void SetGameState(GameState state);
};