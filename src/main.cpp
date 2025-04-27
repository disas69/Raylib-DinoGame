#include "game/DinoGame.h"
#include <raylib-cpp.hpp>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "Dino Run");
    window.SetState(FLAG_VSYNC_HINT);
    window.SetTargetFPS(60);

    DinoGame game;

    while (!window.ShouldClose() && !game.ShouldClose())
    {
        game.UpdateGame(window.GetFrameTime());
        game.DrawGame(window);
    }

    return 0;
}
