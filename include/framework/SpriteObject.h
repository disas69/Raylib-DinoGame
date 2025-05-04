#pragma once

#include "framework/GameObject2D.h"
#include <Texture.hpp>

#define DRAW_DEBUG_RECT 0

class SpriteObject : public framework::GameObject2D
{
public:
    explicit SpriteObject(raylib::Texture* texture) : m_texture(texture) {}
    explicit SpriteObject(raylib::Texture* texture, const Vector2& position) : GameObject2D(position), m_texture(texture) {}

    void SetTexture(raylib::Texture* texture)
    {
        m_texture = texture;
    }

    void Draw() const override
    {
        if (!m_isActive)
        {
            return;
        }

        if (m_texture != nullptr)
        {
#if DRAW_DEBUG_RECT
            const float width = static_cast<float>(m_texture->GetWidth());
            const float height = static_cast<float>(m_texture->GetHeight());
            const Vector2 origin = {width / 2, height / 2};
            DrawRectanglePro(GetRectangle(), origin, m_rotation, BLUE);
#endif
            m_texture->Draw(m_position, m_rotation, 1.0f, m_color);
        }
    }

    Rectangle GetRectangle() const
    {
        if (m_texture != nullptr)
        {
            const float width = static_cast<float>(m_texture->GetWidth());
            const float height = static_cast<float>(m_texture->GetHeight());
            return {m_position.x + width / 2, m_position.y + height / 2, width, height};
        }

        return {0, 0, 0, 0};
    }

private:
    raylib::Texture* m_texture = nullptr;
};