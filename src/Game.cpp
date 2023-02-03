#include "Game.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

Game::Game(int screenWidth, int screenHeight, int FPS, const std::string &title) : screenWidth(screenWidth),
                                                                                   screenHeight(screenHeight),
                                                                                   FPS(FPS) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), title);
}

void Game::ProcessEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::Resized) {
            // keep aspect ratio of the window
            // fixme please
            auto aspectRatio = static_cast<float>(screenWidth) / screenHeight;
            auto newWidth = event.size.height * aspectRatio;
            auto newHeight = event.size.width / aspectRatio;
            if (newWidth > event.size.width) {
                window->setSize({static_cast<unsigned int>(newWidth),
                                 event.size.height});
            } else {
                window->setSize({event.size.width,
                                 static_cast<unsigned int>(newHeight)});
            }
        }
    }
}

void Game::run() {
    TextureManager::instance()->loadTextureFromFile("floor",
                                                    "../resources/rifle/idle/idle.png",
                                                    {{0,   0},
                                                     {313, 313}});

    auto g = std::make_unique<GameObject>();
    g->setSpriteFromTextureManager("floor");
    g->setPosition(100, 0);
    g->setScale(0.8, 0.8);
    gameObjects.push_back(std::move(g));

    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / FPS);
    sf::Time timePerAnimation = sf::seconds(1.0f / 10);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timeSinceLastAnimation = sf::Time::Zero;


    while (window->isOpen()) {
        auto deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        timeSinceLastAnimation += deltaTime;
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            ProcessEvents();
            update(timePerFrame);
        }
        draw(deltaTime);
    }
}

void Game::draw(sf::Time deltaTime) {
    window->clear(sf::Color::Black);
    for (auto &gameObject: gameObjects) {
        window->draw(*gameObject);
    }
    window->display();
}

void Game::update(sf::Time deltaTime) {

}
