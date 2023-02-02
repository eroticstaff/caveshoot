#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable, public sf::Transformable {
  sf::Sprite m_sprite;

public:
  GameObject(sf::Sprite sprite) : m_sprite(sprite) {}
  GameObject() = default;

  void setSpriteFromFile(const std::string &texture_path,
                         const sf::IntRect &areath);

  void setSpriteFromTextureManager(const std::string &name);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};