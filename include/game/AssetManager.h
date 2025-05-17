#pragma once

#include <Font.hpp>
#include <string>
#include <unordered_map>
#include <Texture.hpp>

#define TEXTURES_PATH "resources/sprites/"
#define FONTS_PATH "resources/fonts/"

class AssetManager
{
public:
    AssetManager() = default;
    ~AssetManager() = default;

    void LoadAssets();
    void UnloadAssets();

    raylib::Texture* GetTexture(const std::string& name);
    raylib::Font* GetFont(const std::string& name);

private:
    std::unordered_map<std::string, raylib::Texture> m_textures;
    std::unordered_map<std::string, raylib::Font> m_fonts;
};
