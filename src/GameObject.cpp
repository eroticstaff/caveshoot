#include "Player.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include "TextureManager.h"

void GameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = getTransform();
    target.draw(m_sprite, states);
};

void GameObject::setSpriteFromFile(const std::string &texture_path,
                                   const sf::IntRect &area) {
    auto texture = TextureManager::instance()->loadTextureFromFile(
            "floor", texture_path, area);

    m_sprite.setTexture(*texture);
}

void GameObject::setSpriteFromTextureManager(const std::string &name) {
    m_sprite.setTexture(*TextureManager::instance()->getTextureByName(name));
}

void GameObject::drawOrigin(sf::RenderTarget &target, const sf::RenderStates &states) const {
    sf::CircleShape circle(2);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(getPosition());
    target.draw(circle, states);
}

void GameObject::drawBoundingBox(sf::RenderTarget &target, const sf::RenderStates &states) const {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
    rect.setPosition(getPosition());
    rect.setOrigin(getOrigin());
    rect.setRotation(getRotation());
    target.draw(rect, states);
}