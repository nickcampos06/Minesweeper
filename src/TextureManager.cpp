#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string file_name) {
    string path = "images/";
    path += file_name + ".png";

    textures[file_name].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(std::string texture_name) {
    if (textures.find(texture_name) == textures.end()) {
        LoadTexture(texture_name);
    }

    return textures[texture_name];
}
void TextureManager::Clear() {
    textures.clear();
}