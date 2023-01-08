#include "SFML/Graphics.hpp"
#include "config.h"

#include "VirtualDisplayTFT.h"
#include "Game.h"

/* Please don't make any changes here (edit Game/Game.cpp) */
int main(int argc, char* argv[]) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);

    VirtualDisplayTFT tft(&window);
    InputManager inputManager(&window);
    Game game(&tft, &inputManager);

    game.init();
    int status = game.run();

    window.close();
    exit(status);
}