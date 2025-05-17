#pragma once

#include "framework/SpriteObject.h"
#include <vector>

class SpriteAnimation
{
public:
    SpriteAnimation() = default;

    raylib::Texture* GetCurrentFrame() const
    {
        if (m_frames.empty())
        {
            return nullptr;
        }

        return m_frames[m_currentFrame];
    }

    void AddFrame(raylib::Texture* frame)
    {
        m_frames.push_back(frame);
    }

    void SetFrameTime(float frameTime)
    {
        m_frameTime = frameTime;
    }

    void SetLooping(bool isLooping)
    {
        m_isLooping = isLooping;
    }

    void Play()
    {
        m_isPlaying = true;
        m_currentTime = 0.0f;
        m_currentFrame = 0;
    }

    void Stop()
    {
        m_isPlaying = false;
    }

    void Update(float deltaTime)
    {
        if (!m_isPlaying || m_frames.empty())
        {
            return;
        }

        m_currentTime += deltaTime;

        if (m_currentTime >= m_frameTime)
        {
            m_currentTime -= m_frameTime;
            m_currentFrame++;

            if (m_currentFrame >= static_cast<int>(m_frames.size()))
            {
                if (m_isLooping)
                {
                    m_currentFrame = 0;
                }
                else
                {
                    m_currentFrame--;
                    Stop();
                }
            }
        }
    }

private:
    std::vector<raylib::Texture*> m_frames;
    float m_frameTime = 0.0f;
    float m_currentTime = 0.0f;
    int m_currentFrame = 0;
    bool m_isLooping = false;
    bool m_isPlaying = false;
};