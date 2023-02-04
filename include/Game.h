#pragma once

#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>

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
    static Game instance(800, 600, 30, "Test");
    return &instance;
  }

  void addGameObject(std::unique_ptr<GameObject> gameObject);

  void removeGameObject(GameObject *gameObject);

  bool isDebugDraw() const;

  int getGameObjectsCount();

  sf::RenderWindow *getWindow() const;

private:
  int screenWidth = 800;
  int screenHeight = 600;
  int FPS = 300;

  bool debugDraw = false;

  std::unique_ptr<sf::RenderWindow> window;
  std::vector<std::unique_ptr<GameObject>> gameObjects;
};
