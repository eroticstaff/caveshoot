#include "GameObject.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

  TextureManager::instance()->loadTextureFromFile(
      "floor", "../resources/tiles/floor/floor_side4.png", {{0, 0}, {16, 16}});

  GameObject g;

  g.setSpriteFromTextureManager("floor");

  g.setPosition(100, 0);
  g.setScale(5, 5);
  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);

    window.draw(g);

    window.display();
  }

  return 0;
}