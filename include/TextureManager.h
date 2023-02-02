#pragma once

#include <SFML/Graphics.hpp>
#include <exception>
#include <string.h>
#include <unordered_map>

class TextureManager {
  std::unordered_map<std::string, sf::Texture *> storage;

private:
  TextureManager() = default;

public:
  static TextureManager *instance() {
    static TextureManager tm;
    return &tm;
  }

  sf::Texture *loadTextureFromFile(const std::string &name,
                                   const std::string &texture_path,
                                   const sf::IntRect &area);

  sf::Texture *getTextureByName(const std::string &name);

  ~TextureManager() {
    for (auto tuple : storage) {
      delete tuple.second;
    }
  }
};
