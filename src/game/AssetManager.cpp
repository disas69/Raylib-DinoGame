#include "game/AssetManager.h"

void AssetManager::LoadAssets()
{
    // Load textures
    m_textures["dino"] = raylib::Texture(TEXTURES_PATH "Dino_Idle.png");
    m_textures["dino_run_1"] = raylib::Texture(TEXTURES_PATH "Dino_Run01.png");
    m_textures["dino_run_2"] = raylib::Texture(TEXTURES_PATH "Dino_Run02.png");
    m_textures["cactus"] = raylib::Texture(TEXTURES_PATH "Cactus_Small_Single.png");
    m_textures["ground"] = raylib::Texture(TEXTURES_PATH "Ground.png");

    // Load fonts
    m_fonts["main"] = raylib::Font(FONTS_PATH "PublicPixel.ttf");
}

void AssetManager::UnloadAssets()
{
    for (auto& texture : m_textures)
    {
        texture.second.Unload();
    }
    m_textures.clear();

    for (auto& font : m_fonts)
    {
        font.second.Unload();
    }
    m_fonts.clear();
}

raylib::Texture* AssetManager::GetTexture(const std::string& name)
{
    if (m_textures.find(name) != m_textures.end())
    {
        return &m_textures[name];
    }

    TraceLog(LOG_WARNING, "Texture %s not found", name.c_str());
    return nullptr;
}

raylib::Font* AssetManager::GetFont(const std::string& name)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        return &m_fonts[name];
    }

    TraceLog(LOG_WARNING, "Font %s not found", name.c_str());
    return nullptr;
}