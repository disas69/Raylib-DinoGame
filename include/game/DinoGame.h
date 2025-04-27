#pragma once

#include "framework/GameBase.h"

class DinoGame : public framework::GameBase
{
public:
    DinoGame()
    {
        Load();
    }

    ~DinoGame() override
    {
        Unload();
    }

    void UpdateGame(float deltaTime) override;
    void DrawGame(raylib::Window& window) override;

private:
    void Load();
    void Unload();
};