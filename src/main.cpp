#include "GameObject.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(3000, 1000), "My window");

  TextureManager::instance()->loadTextureFromFile(
      "floor", "../resources/rifle/idle/idle.png", {{0, 0}, {313, 313}});

  GameObject g;

  g.setSpriteFromTextureManager("floor");

  g.setPosition(100, 0);
  g.setScale(0.8, 0.8);
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