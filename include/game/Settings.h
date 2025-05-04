#pragma once

struct PlayerSettings
{
    float MovementSpeed = 650.f;
    float JumpSpeed = 800.f;
    float JumpHeight = 250.f;
};

struct GameSettings
{
    PlayerSettings PlayerSettings;
};