#include "TextureManager.h"
#include "Exceptions.h"

sf::Texture *
TextureManager::loadTextureFromFile(const std::string &name,
                                    const std::string &texture_path,
                                    const sf::IntRect &area) {
  if (storage.contains(name))
    throw NameAlreadyTakenForTextureException(name);
  sf::Texture *texture = new sf::Texture;
  if (not texture->loadFromFile(texture_path, area))
    throw NoSuchFileException(texture_path);

  storage[name] = texture;
  return texture;
}

sf::Texture *TextureManager::getTextureByName(const std::string &name) {
  if (not storage.contains(name))
    throw NoSuchTextureWithNameException(name);
  return storage[name];
}
