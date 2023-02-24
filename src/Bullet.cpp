#include "Bullet.h"
#include "Game.h"

float Bullet::speed = 10.f;

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  GameObject::draw(target, states);
  if (Game::get_instance()->isDebugDraw()) {
    drawBoundingBox(target, states);
    drawOrigin(target, states);
  }
}

void Bullet::update(sf::Time deltaTime) {
  auto pos = getPosition();
  pos += m_velocity * speed * deltaTime.asSeconds();
  setPosition(pos);
  checkOutOfScope();
}

void Bullet::checkOutOfScope() {
  auto posititon = getPosition();
  auto window = Game::get_instance()->getWindow();
  if (posititon.x < 0 || posititon.x > window->getSize().x || posititon.y < 0 ||
      posititon.y > window->getSize().y) {
    Game::get_instance()->removeGameObject(this);
  }
}

Bullet::Bullet() {
  setSpriteFromTextureManager("bullet");
  setOrigin(m_sprite.getLocalBounds().width / 2,
            m_sprite.getLocalBounds().height / 2);
}

void Bullet::ProcessEvents(sf::Event &event) {}
