#include "game/Game.h"
#include <raylib-cpp.hpp>

int main()
{
    const GameSettings settings;

    raylib::Window window(settings.ScreenWidth, settings.ScreenHeight, settings.Name);
    window.SetState(FLAG_VSYNC_HINT);
    window.SetTargetFPS(60);

    Game game(settings);

    while (!window.ShouldClose() && !game.ShouldClose())
    {
        game.UpdateGame(window.GetFrameTime());
        game.DrawGame(window);
    }

    return 0;
}
