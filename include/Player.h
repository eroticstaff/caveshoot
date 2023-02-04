#pragma once

#include "GameObject.h"

class Player : public GameObject {
private:
    sf::Vector2f m_velocity;
    float rotation = 0;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(sf::Time deltaTime) override;

public:
    static float speed;

    Player();

    void ProcessEvents(sf::Event &event) override;

    void spawnBullet() const;
};