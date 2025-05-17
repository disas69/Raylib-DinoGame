#pragma once

struct PlayerSettings
{
    float MovementSpeed = 650.f;
    float JumpDuration = 0.575f;
    float JumpHeightMin = 100.f;
    float JumpHeightMax = 200.f;
    float StartOffset = 150.0f;
    float GroundOffset = 50.0f;
};

struct GameSettings
{
    PlayerSettings Player;

    int ScreenWidth = 0;
    int ScreenHeight = 0;
    float CameraXOffset = 380.0f;
    float CameraYOffset = -30.0f;
};