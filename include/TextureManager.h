#pragma once

#include <SFML/Graphics.hpp>
#include <exception>
#include <string>
#include <unordered_map>
#include <memory>

class TextureManager {
    using TexturePointer = std::shared_ptr<sf::Texture>;
    std::unordered_map<std::string, TexturePointer> storage;

private:
    TextureManager() = default;

    TextureManager(const TextureManager &) = default;

    TextureManager &operator=(const TextureManager &) = default;

public:


    static TextureManager *instance() {
        static TextureManager tm;
        return &tm;
    }

    TexturePointer loadTextureFromFile(const std::string &name,
                                       const std::string &texture_path,
                                       const sf::IntRect &area);

    TexturePointer getTextureByName(const std::string &name);
};
