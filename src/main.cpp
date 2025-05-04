#include "game/Game.h"
#include <raylib-cpp.hpp>

int main()
{
    constexpr int screenWidth = 900;
    constexpr int screenHeight = 400;

    raylib::Window window(screenWidth, screenHeight, "Dino Run");
    window.SetState(FLAG_VSYNC_HINT);
    window.SetTargetFPS(60);

    Game game;
    while (!window.ShouldClose() && !game.ShouldClose())
    {
        game.UpdateGame(window.GetFrameTime());
        game.DrawGame(window);
    }

    return 0;
}
