#pragma once

#include "GameObject.h"

class Bullet : public GameObject {
private:
    float rotation = 0;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime) override;

public:
    sf::Vector2f m_velocity;
    static float speed;

    Bullet();

    void ProcessEvents(sf::Event &event) override;

    void checkOutOfScope();
};