#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>
#include <algorithm>

class CompositeGameObject : public GameObject {
private:
    std::vector<std::unique_ptr<GameObject>> children;

public:
    CompositeGameObject();

    void update(sf::Time deltaTime) override;

    void ProcessEvents(sf::Event &event) override;

    void addChild(GameObject *child);

    void removeChild(GameObject *child);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};