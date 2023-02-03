#include "GameObject.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Game.h>

int main() {
    Game g(800, 600, 300, "Test");
    g.run();
    return 0;
}