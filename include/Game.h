#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

class Game {
public:
    Game(int screenWidth, int screenHeight, int FPS, const std::string &title);

    void ProcessEvents();

    void run();

    void draw(sf::Time deltaTime);

    void update(sf::Time deltaTime);

private:
    int screenWidth = 800;
    int screenHeight = 600;
    int FPS = 300;
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};

