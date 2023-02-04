#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

class GameObject : public sf::Drawable, public sf::Transformable {

public:
    explicit GameObject(sf::Sprite sprite) : m_sprite(std::move(sprite)) {}

    GameObject() = default;

    void setSpriteFromFile(const std::string &texture_path,
                           const sf::IntRect &areath);

    void setSpriteFromTextureManager(const std::string &name);

    virtual void ProcessEvents(sf::Event &event) = 0;

    virtual void update(sf::Time deltaTime) = 0;

protected:
    sf::Sprite m_sprite;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void drawOrigin(sf::RenderTarget &target, const sf::RenderStates &states) const;

    void drawBoundingBox(sf::RenderTarget &target, const sf::RenderStates &states) const;
};