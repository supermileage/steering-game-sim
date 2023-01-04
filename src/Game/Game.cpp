#include "Game.h"

Game::Game(SPI_TFT_ILI9341* tft) : _tft(tft) {
    _timer = new Timer();
}

void Game::init() {
    _timer->start();
    _tft->cls();

    /* Initialize any game objects here */
}

void Game::run() {
    while (_run) {
        /* Define all game-related behavior here */
        
    }
}