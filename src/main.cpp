#include "SFML/Graphics.hpp"
#include "Game.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define GAME_NAME "Pong"

int main(int argc, char* argv[]) {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);

    VirtualDisplayTFT tft(&window);
    InputManager inputManager(&window);
    Game game(&tft, &inputManager);

    game.init();
    int ret = game.run();

    window.close();
    return ret;
}