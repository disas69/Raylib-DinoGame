#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include "game/UIManager.h"

void UIManager::Initialize(raylib::Font* font, raylib::Texture* restartIcon, int screenWidth, int screenHeight)
{
    m_font = font;
    m_restartIcon = restartIcon;
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    Reset();
}

void UIManager::Draw(GameState gameState, int score, int highScore)
{
    if (gameState == GameState::None)
    {
        return;
    }

    if (gameState == GameState::Start)
    {
        DrawStartState();
    }
    else if (gameState == GameState::Play)
    {
        DrawPlayState(score, highScore);
    }
    else if (gameState == GameState::GameOver)
    {
        DrawGameOverState(score, highScore);
    }

    if (gameState == GameState::Start || m_isStartAnimationPlaying)
    {
        DrawRectangleV(m_startAnimationRectPosition, {static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight)}, RAYWHITE);
    }
}

void UIManager::Update(float deltaTime)
{
    if (m_isStartAnimationPlaying)
    {
        m_startAnimationTime += deltaTime;

        const int endX = m_screenWidth;

        if (m_startAnimationTime >= START_ANIMATION_DURATION)
        {
            m_startAnimationTime = 0.0f;
            m_isStartAnimationPlaying = false;

            m_startAnimationRectPosition.SetX(endX);
        }
        else
        {
            const int startX = START_ANIMATION_POSITION;
            const int lerpX = Lerp(startX, endX, m_startAnimationTime / START_ANIMATION_DURATION);
            m_startAnimationRectPosition.SetX(lerpX);
        }
    }
}

void UIManager::PlayStartAnimation()
{
    m_startAnimationTime = 0.0f;
    m_isStartAnimationPlaying = true;
}

void UIManager::Reset()
{
    m_isRestartButtonPressed = false;
    m_startAnimationRectPosition = raylib::Vector2(START_ANIMATION_POSITION, -80);
}

void UIManager::DrawStartState()
{
    DrawTextEx(*m_font, "Press space to start", {25, static_cast<float>(m_screenHeight) - 65}, 18, 0, UI_COLOR);
}

void UIManager::DrawPlayState(int score, int highScore)
{
    const std::string scoreText = "HI " + FormatScore(highScore) + " " + FormatScore(score);
    const int textWidth = MeasureTextEx(*m_font, scoreText.c_str(), 18, 0).x;
    DrawTextEx(*m_font, scoreText.c_str(), {static_cast<float>(m_screenWidth) - textWidth - 15, 15}, 18, 0, UI_COLOR);
}

void UIManager::DrawGameOverState(int score, int highScore)
{
    DrawPlayState(score, highScore);

    int textWidth = MeasureTextEx(*m_font, "GAME OVER", 24, 0).x;
    DrawTextEx(*m_font, "GAME OVER", {static_cast<float>(m_screenWidth) / 2 - textWidth / 2, static_cast<float>(m_screenHeight) / 2 - 60}, 24, 0, UI_COLOR);

    // Drawing button underneath the actual restart icon
    raylib::Vector2 restartIconPosition = {static_cast<float>(m_screenWidth) / 2 - m_restartIcon->GetSize().x / 2, static_cast<float>(m_screenHeight) / 2 - 20};
    if (GuiButton({restartIconPosition.x + 3, restartIconPosition.y + 3, m_restartIcon->GetSize().x - 6, m_restartIcon->GetSize().y - 6}, ""))
    {
        m_isRestartButtonPressed = true;
    }

    m_restartIcon->Draw(restartIconPosition, WHITE);
}

std::string UIManager::FormatScore(int score) const
{
    // Format score to 5 digits with leading zeros
    return std::to_string(score).insert(0, 5 - std::to_string(score).length(), '0');
}