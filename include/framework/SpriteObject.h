#pragma once

#include "framework/GameObject2D.h"
#include <Texture.hpp>

#define DRAW_DEBUG_RECT 0

class SpriteObject : public framework::GameObject2D
{
public:
    explicit SpriteObject(raylib::Texture* texture) : m_texture(texture) {}
    explicit SpriteObject(raylib::Texture* texture, const Vector2& position) : GameObject2D(position), m_texture(texture) {}

    raylib::Texture* GetTexture() const
    {
        return m_texture;
    }

    void SetTexture(raylib::Texture* texture)
    {
        m_texture = texture;
    }

    int GetWidth() const
    {
        return m_texture->GetWidth();
    }

    int GetHeight() const
    {
        return m_texture->GetHeight();
    }

    void SetRectOffsets(float widthOffset, float heightOffset)
    {
        m_widthOffset = widthOffset;
        m_heightOffset = heightOffset;
    }

    void Draw() const override
    {
        if (!m_isActive)
        {
            return;
        }

#if DRAW_DEBUG_RECT
        DrawRectangleRec(GetRectangle(), BLUE);
#endif
        if (m_texture != nullptr)
        {
            m_texture->Draw(m_position, m_rotation, 1.0f, m_color);
        }
    }

    Rectangle GetRectangle() const
    {
        if (m_texture != nullptr)
        {
            const float width = static_cast<float>(m_texture->GetWidth());
            const float height = static_cast<float>(m_texture->GetHeight());
            return {m_position.x + m_widthOffset / 2, m_position.y + m_heightOffset / 2, width - m_widthOffset, height - m_heightOffset};
        }

        return {0, 0, 0, 0};
    }

private:
    raylib::Texture* m_texture = nullptr;
    float m_widthOffset = 0.0f;
    float m_heightOffset = 0.0f;
};