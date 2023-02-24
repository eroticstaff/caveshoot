#pragma once

#include <string>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include <Network.h>

class Game {
public:
    Game(int screenWidth, int screenHeight, int FPS, const std::string &title);

    void ProcessEvents();

    void run();

    void draw(sf::Time deltaTime);

    void draw_gui(sf::Time deltaTime);

    void update(sf::Time deltaTime);

    ~Game();

    static Game *get_instance() {
        static Game instance(1920, 1080, 30, "Test");
        return &instance;
    }

    void addGameObject(std::unique_ptr<GameObject> gameObject);

    void removeGameObject(GameObject *gameObject);

    sf::RenderWindow *getWindow() const;

private:
    char command[100];
    Network network;
    int screenWidth = 800;
    int screenHeight = 600;
    int FPS = 300;
    std::unique_ptr<sf::RenderWindow> window;
    std::vector<std::unique_ptr<GameObject>> gameObjects;

};

