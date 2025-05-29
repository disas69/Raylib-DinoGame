#pragma once

#include <string>

struct PlayerSettings
{
    float MovementSpeed = 650.f;
    float JumpDuration = 0.575f;
    float JumpHeightMin = 100.f;
    float JumpHeightMax = 200.f;
    float StartOffset = 150.0f;
    float GroundOffset = 50.0f;
};

struct ObstacleSettings
{
    int Offset = 1000;
    int MinSpawnDistance = 300;
    int MaxSpawnDistance = 900;
};

struct GameSettings
{
    PlayerSettings Player;
    ObstacleSettings Obstacle;

    std::string Name = "Dino Run";
    int ScreenWidth = 900;
    int ScreenHeight = 400;
    float CameraXOffset = 380.0f;
    float CameraYOffset = -30.0f;
};