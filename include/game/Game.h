#pragma once

#include "GameState.h"
#include "AssetManager.h"
#include "Obstacle.h"
#include "framework/GameBase.h"
#include "framework/SpriteObject.h"
#include "Player.h"
#include "Settings.h"
#include "UIManager.h"
#include <vector>
#include <memory>

#define OBSTACLE_POOL_SIZE 10
#define GROUND_POOL_SIZE 2

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
    UIManager m_uiManager;

    raylib::Camera2D m_camera;
    std::unique_ptr<Player> m_player = nullptr;
    std::vector<std::unique_ptr<Obstacle>> m_obstacles = {};
    std::vector<std::unique_ptr<SpriteObject>> m_grounds = {};

    GameState m_gameState = GameState::None;
    int m_score = 0;
    int m_bestScore = 0;
    int m_groundIndex = 0;
    int m_obstacleOffset = 0;

    void Initialize();
    void Dispose();
    void SetGameState(GameState state);
    void LoadData();
    void SaveData();
};