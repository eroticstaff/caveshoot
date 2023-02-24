#include "Game.h"
#include "TextureManager.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "Player.h"
#include "Bullet.h"
#include "CompositeGameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

Game::Game(int screenWidth, int screenHeight, int FPS, const std::string &title) : screenWidth(screenWidth),
                                                                                   screenHeight(screenHeight),
                                                                                   FPS(FPS) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), title);
    ImGui::SFML::Init(*window);
    window->setFramerateLimit(FPS);
    ImGui::GetIO().FontGlobalScale = 3;
}

void Game::ProcessEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*window, event);
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::Resized) {
            // keep consistent view
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));

        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Q) {
                window->close();
            }
        }
        for (auto &gameObject: gameObjects) {
            gameObject->ProcessEvents(event);
        }
    }
}

void Game::run() {
    TextureManager::instance()->loadTextureFromFile("player",
                                                    "../resources/rifle/idle/idle.png",
                                                    {{0,   0},
                                                     {313, 313}});
    TextureManager::instance()->loadTextureFromFile("bullet",
                                                    "../resources/props_itens/barrel.png",
                                                    {{0,  0},
                                                     {16, 16}});

    auto player = std::make_unique<Player>();
    player->setSpriteFromTextureManager("player");
    gameObjects.push_back(std::move(player));

    // create composite game object
    auto compositeGameObject = std::make_unique<CompositeGameObject>();
    for (int i = 0; i < 10; i++) {
        auto bullet = std::make_unique<Bullet>();
        bullet->setSpriteFromTextureManager("bullet");
        bullet->setPosition({(float) i * 10, (float) i * 10});
        compositeGameObject->addChild(bullet.release());
    }
    CompositeGameObject *weakCompositeGameObject = compositeGameObject.get();
    gameObjects.push_back(std::move(compositeGameObject));

    sf::Clock clock;

    while (window->isOpen()) {
        ProcessEvents();
        auto deltaTime = clock.restart();
        if (weakCompositeGameObject)
            weakCompositeGameObject->setPosition(weakCompositeGameObject->getPosition() + sf::Vector2f(1, 1));
        update(deltaTime);
        draw(deltaTime);
    }
}

void Game::update(sf::Time deltaTime) {
    ImGui::SFML::Update(*window, deltaTime);
    for (auto &gameObject: gameObjects) {
        gameObject->update(deltaTime);
    }
    network.recieve();
}

void Game::draw(sf::Time deltaTime) {
    window->clear(sf::Color::Black);
    for (auto &gameObject: gameObjects) {
        window->draw(*gameObject);
    }
    // draw point at cursor position
    sf::CircleShape shape(2);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
    window->draw(shape);
    draw_gui(sf::Time());
    window->display();
}

void Game::draw_gui(sf::Time deltaTime) {
    ImGui::Begin("Hello, world!");
    ImGui::SliderFloat("Player Speed", &Player::speed, 0.0f, 1000.0f);
    ImGui::SliderFloat("Bullet Speed", &Bullet::speed, 0.0f, 10.0f);
    ImGui::Text("Number of game objects: %zu", gameObjects.size());

    ImGui::InputText("Command", command, 100);
    ImGui::Text(network.isConnected() != sf::Socket::Done ? "error" : "connected");
    if (ImGui::Button("Run command")) {
        std::cout << command << std::endl;
        network.send(command);
    }
    if (ImGui::Button("connect to server")) {
        network.connect();
    }
    if (ImGui::Button("exit")) {
        window->close();
    }
    ImGui::TextColored(ImVec4{0, 1, 0, 1}, network.get_result().c_str());

    ImGui::End();

    ImGui::SFML::Render(*window);
}

Game::~Game() {
    ImGui::SFML::Shutdown();

}

void Game::addGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Game::removeGameObject(GameObject *gameObject) {
//    gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
//                                     [gameObject](const std::unique_ptr<GameObject> &obj) {
//                                         return obj.get() == gameObject;
//                                     }), gameObjects.end());
}

sf::RenderWindow *Game::getWindow() const {
    return window.get();
}
