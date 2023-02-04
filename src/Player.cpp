#include "Player.h"
#include "Bullet.h"
#include "Game.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>

float Player::speed = 300.f;

Player::Player() {
  setSpriteFromTextureManager("player");
  setOrigin(m_sprite.getLocalBounds().width / 2 - 55,
            m_sprite.getLocalBounds().height / 2 + 15);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  GameObject::draw(target, states);
  if (Game::get_instance()->isDebugDraw()) {
    drawBoundingBox(target, states);
    drawOrigin(target, states);
  }
}

void Player::update(sf::Time deltaTime) {
  // update transform
  auto pos = getPosition();
  pos += m_velocity * deltaTime.asSeconds();
  setPosition(pos);
}

void Player::ProcessEvents(sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::W) {
      m_velocity.y = -speed;
    } else if (event.key.code == sf::Keyboard::S) {
      m_velocity.y = speed;
    } else if (event.key.code == sf::Keyboard::A) {
      m_velocity.x = -speed;
    } else if (event.key.code == sf::Keyboard::D) {
      m_velocity.x = speed;
    }
  } else if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::W) {
      m_velocity.y = 0;
    } else if (event.key.code == sf::Keyboard::S) {
      m_velocity.y = 0;
    } else if (event.key.code == sf::Keyboard::A) {
      m_velocity.x = 0;
    } else if (event.key.code == sf::Keyboard::D) {
      m_velocity.x = 0;
    }
  }
  if (event.type == sf::Event::MouseMoved) {
    auto pos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    auto player_pos = getPosition();
    auto diff = pos - player_pos;
    rotation = std::atan2(diff.y, diff.x) * 180 / M_PI;
    setRotation(rotation);
  }
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      // spawnBullet();
    }
  }
}

void Player::spawnBullet() const {
  auto bullet = std::make_unique<Bullet>();
  bullet->setPosition(getPosition());
  bullet->setRotation(getRotation());
  bullet->m_velocity =
      sf::Vector2f(std::cos(getRotation() * M_PI / 180) * speed,
                   std::sin(getRotation() * M_PI / 180) * speed);
  bullet->setScale(5, 5);
  Game::get_instance()->addGameObject(std::move(bullet));
}
