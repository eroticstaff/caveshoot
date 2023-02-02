#include "GameObject.h"
#include "TextureManager.h"

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform = getTransform();
  target.draw(m_sprite, states);
};

void GameObject::setSpriteFromFile(const std::string &texture_path,
                                   const sf::IntRect &area) {
  sf::Texture *texture = TextureManager::instance()->loadTextureFromFile(
      "floor", texture_path, area);

  m_sprite.setTexture(*texture);
}

void GameObject::setSpriteFromTextureManager(const std::string &name) {
  m_sprite.setTexture(*TextureManager::instance()->getTextureByName(name));
}