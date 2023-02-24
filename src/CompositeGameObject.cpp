#include "CompositeGameObject.h"

CompositeGameObject::CompositeGameObject() = default;

void CompositeGameObject::addChild(GameObject *child) {
    children.push_back(std::unique_ptr<GameObject>(child));
}

void CompositeGameObject::removeChild(GameObject *child) {
    children.erase(
            std::remove_if(children.begin(), children.end(), [child](const std::unique_ptr<GameObject> &element) {
                return element.get() == child;
            }), children.end());
}

void CompositeGameObject::ProcessEvents(sf::Event &event) {
    for (auto &child: children) {
        child->ProcessEvents(event);
    }
}

void CompositeGameObject::update(sf::Time deltaTime) {
    for (auto &child: children) {
        child->update(deltaTime);
    }
}

void CompositeGameObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    GameObject::draw(target, states);
    states.transform *= getTransform();
    for (auto &child: children)
        target.draw(*child, states);
}
