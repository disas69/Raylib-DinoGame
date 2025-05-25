#pragma once

#include "GameState.h"
#include <Font.hpp>
#include <Texture.hpp>
#include <string>

#define UI_COLOR CLITERAL(Color){ 83, 83, 83, 255 }
#define START_ANIMATION_DURATION 0.66f
#define START_ANIMATION_POSITION 200

class UIManager
{
public:
    UIManager() = default;
    ~UIManager() = default;

    void Initialize(raylib::Font* font, raylib::Texture* restartIcon, int screenWidth, int screenHeight);
    void Draw(GameState gameState, int score, int highScore);
    void Update(float deltaTime);
    void PlayStartAnimation();
    void Reset();

    bool ShouldRestart() const
    {
        return m_isRestartButtonPressed;
    }

private:
    raylib::Font* m_font = nullptr;
    raylib::Texture* m_restartIcon = nullptr;
    int m_screenWidth = 0;
    int m_screenHeight = 0;

    raylib::Vector2 m_startAnimationRectPosition = {0.0f, 0.0f};
    float m_startAnimationTime = 0.0f;
    bool m_isStartAnimationPlaying = false;
    bool m_isRestartButtonPressed = false;

    void DrawStartState();
    void DrawPlayState(int score, int highScore);
    void DrawGameOverState(int score, int highScore);

    std::string FormatScore(int score) const;
};