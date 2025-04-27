#include "raylib-cpp.hpp"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    raylib::Window window(screenWidth, screenHeight, "Dino Run");
    window.SetState(FLAG_VSYNC_HINT);
    window.SetTargetFPS(60);

    // Load game

    while (!WindowShouldClose())
    {
        // Update game

        // Draw game
        window.BeginDrawing();
        window.ClearBackground(RAYWHITE);

        raylib::DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        window.EndDrawing();
    }

    // Unload game

    return 0;
}
