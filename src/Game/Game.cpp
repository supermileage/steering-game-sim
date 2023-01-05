#include "Game.h"

using namespace std::chrono;

Game::Game(SPI_TFT_ILI9341* tft, InputManager* inputManager) : _tft(tft), _inputManager(inputManager) {
    _timer = new Timer();
    _inputManager->setGame(this);
    _inputManager->setButtonPressedCallback1(&Game::_handleButtonPressed1);
    _inputManager->setButtonReleasedCallback1(&Game::_handleButtonReleased1);
    _inputManager->setButtonPressedCallback2(&Game::_handleButtonPressed2);
    _inputManager->setButtonReleasedCallback2(&Game::_handleButtonReleased2);
    _inputManager->setCloseRequestCallback(&Game::_handleCloseRequest);
}

Game::~Game() {
    delete _timer;
}

void Game::init() {
    _timer->start();
    _tft->background(Black);
    _tft->cls();

    /* Initialize any game objects here */
}

int Game::run() {
    while (_run) {
        int64_t currentTime = _millis();
        _inputManager->run();

        Vec2 curJoystickPos = _inputManager->currentJoystickPos();
        if (curJoystickPos != _lastJoystickPos) {
            _handleJoystickChanged(curJoystickPos);
            _lastJoystickPos = curJoystickPos;
        }

        _loop();
    }

    return 1;
}

void Game::_loop() {
    /* Game loop */
}

void Game::_handleJoystickChanged(Vec2 pos) {
    /* handle joystick-related behavior */
}

void Game::_handleButtonPressed1() {
    /* Button 1 press behavior here */
}

void Game::_handleButtonReleased1() {
    /* Button 1 release behavior here */
}

void Game::_handleButtonPressed2() {
    /* Button 2 press behavior here */
}

void Game::_handleButtonReleased2() {
    /* Button 2 release behavior here */
}

int64_t Game::_millis() {
    return duration_cast<milliseconds>(_timer->elapsed_time()).count();
}

int64_t Game::_micros() {
    return duration_cast<microseconds>(_timer->elapsed_time()).count();
}

void Game::_handleCloseRequest() {
    _run = false;
}
