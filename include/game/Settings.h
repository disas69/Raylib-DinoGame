#pragma once

struct PlayerSettings
{
    float MovementSpeed = 650.f;
    float JumpDuration = 0.575f;
    float JumpHeightMin = 100.f;
    float JumpHeightMax = 200.f;
};

struct GameSettings
{
    PlayerSettings PlayerSettings;
};