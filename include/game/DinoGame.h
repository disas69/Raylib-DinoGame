#pragma once

#include "framework/GameBase.h"

class DinoGame : public framework::GameBase
{
public:
    DinoGame() { Load(); }
    ~DinoGame() override { Unload(); }

    void UpdateGame(float deltaTime) override;
    void DrawGame(raylib::Window& window) override;

private:
    void Load();
    void Unload();

    raylib::Texture m_dinoTexture;
    raylib::Texture m_obstacleTexture;
    raylib::Texture m_groundTexture;

    float m_groundOffset = 60;
};