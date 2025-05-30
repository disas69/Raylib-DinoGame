﻿#pragma once

#include <raylib.h>

namespace framework
{
class GameObject2D
{
public:
    GameObject2D() : m_position({0.f, 0.f}) {}
    explicit GameObject2D(const Vector2& position) : m_position(position) {}
    explicit GameObject2D(const Color& color) : m_position({0.f, 0.f}), m_color(color) {}
    GameObject2D(const Vector2& position, const Color& color) : m_position(position), m_color(color) {}

    virtual void Draw() const = 0;
    virtual ~GameObject2D() = default;

    void SetActive(const bool isActive) { m_isActive = isActive; }
    bool IsActive() const { return m_isActive; }

    void SetPosition(const Vector2 position) { m_position = position; }
    Vector2 GetPosition() const { return m_position; }

    float GetRotation() const { return m_rotation; }
    void SetRotation(const float rotation) { m_rotation = rotation; }

    void SetColor(const Color& color) { m_color = color; }
    Color GetColor() const { return m_color; }

protected:
    Vector2 m_position = {0.f, 0.f};
    float m_rotation = 0;
    Color m_color = WHITE;
    bool m_isActive = true;
};
}
