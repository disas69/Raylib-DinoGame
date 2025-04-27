#pragma once

#include <raylib-cpp.hpp>

namespace framework
{
class GameBase
{
public:
    explicit GameBase()
    {
        m_screenWidth = GetScreenWidth();
        m_screenHeight = GetScreenHeight();
    }

    virtual ~GameBase() = default;
    virtual void UpdateGame(float deltaTime) = 0;
    virtual void DrawGame(raylib::Window& window) = 0;

    bool ShouldClose() const { return m_shouldClose; }
    void SetShouldClose(bool shouldClose) { m_shouldClose = shouldClose; }

protected:

    float m_screenWidth = 0;
    float m_screenHeight = 0;
    bool m_shouldClose = false;
};
}


