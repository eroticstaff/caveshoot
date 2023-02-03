#include "TextureManager.h"
#include "Exceptions.h"

TextureManager::TexturePointer TextureManager::loadTextureFromFile(const std::string &name,
                                                                   const std::string &texture_path,
                                                                   const sf::IntRect &area) {
    if (storage.contains(name))
        throw NameAlreadyTakenForTextureException(name);
    auto texture = std::make_shared<sf::Texture>();
    if (not texture->loadFromFile(texture_path, area))
        throw NoSuchFileException(texture_path);

    storage[name] = texture;
    return texture;
}

TextureManager::TexturePointer TextureManager::getTextureByName(const std::string &name) {
    if (not storage.contains(name))
        throw NoSuchTextureWithNameException(name);
    return storage[name];
}
