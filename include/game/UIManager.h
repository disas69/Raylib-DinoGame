#pragma once

#include "GameState.h"
#include <Font.hpp>

class UIManager
{
public:
    UIManager() = default;
    ~UIManager() = default;

    void Initialize(raylib::Font* font, int screenWidth, int screenHeight);
    void Draw(GameState gameState, int score, int highScore);

private:
    raylib::Font* m_font = nullptr;
    int m_screenWidth = 0;
    int m_screenHeight = 0;
};