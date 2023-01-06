#include "config.h"
#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow* window) : _window(window) { }

void InputManager::init() { }

void InputManager::run() {
    while (_window->pollEvent(_windowEvent)) {
        switch (_windowEvent.type) {
            case sf::Event::KeyPressed:
                _handleKeyPressed();
                break;
            case sf::Event::KeyReleased:
                _handleKeyReleased();
                break;
            case sf::Event::Closed:
                (_game->*_closeRequestCallback)();
                break;
            default:
                break;
        }
    }
}

void InputManager::setGame(Game* game) {
    _game = game;
}

void InputManager::setButtonPressedCallback1(void (Game::*callback)(void)) {
    _pressedCallback1 = callback;
}

void InputManager::setButtonReleasedCallback1(void (Game::*callback)(void)) {
    _releasedCallback1 = callback;
}

void InputManager::setButtonPressedCallback2(void (Game::*callback)(void)) {
    _pressedCallback2 = callback;
}

void InputManager::setButtonReleasedCallback2(void (Game::*callback)(void)) {
    _releasedCallback2 = callback;
}

void InputManager::setCloseRequestCallback(void (Game::*callback)(void)) {
    _closeRequestCallback = callback;
}

Vec2 InputManager::currentJoystickPos() {
    return Vec2 { 0, 0 };
}

void InputManager::_handleKeyPressed() {
    switch (_windowEvent.key.code) {
        case BUTTON_1:
            (_game->*_pressedCallback1)();
            break;
        case BUTTON_2:
            (_game->*_pressedCallback2)();
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            _updateJoystick(_windowEvent.key.code, sf::Event::KeyPressed);
            break;
        default:
            break;
    }
}

void InputManager::_handleKeyReleased() {
    switch (_windowEvent.key.code) {
        case BUTTON_1:
            (_game->*_releasedCallback1)();
            break;
        case BUTTON_2:
            (_game->*_releasedCallback2)();
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            _updateJoystick(_windowEvent.key.code, sf::Event::KeyReleased);
            break;
        default:
            break;
    }
}

void InputManager::_updateJoystick(sf::Keyboard::Key key, sf::Event::EventType type) {
    switch (key) {
        case sf::Keyboard::Up:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.y = -100;
            } else {
                _currentJoystickPos.y = (_currentJoystickPos.y > 0 ? 100 : 0);
            }
            break;
        case sf::Keyboard::Down:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.y = 100;
            } else {
                _currentJoystickPos.y = (_currentJoystickPos.y < 0 ? -100 : 0);
            }
            break;
        case sf::Keyboard::Left:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.x = -100;
            } else {
                _currentJoystickPos.x = (_currentJoystickPos.x > 0 ? 100 : 0);
            }
            break;
        case sf::Keyboard::Right:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.x = 100;
            } else {
                _currentJoystickPos.x = (_currentJoystickPos.x < 0 ? -100 : 0);
            }
            break;
        default:
            break;
    }

    // check if Vec2 should be 45°
    if (_currentJoystickPos.x != 0 && _currentJoystickPos.y != 0) {
        _currentJoystickPos.x = _currentJoystickPos.x * 0.7071;
        _currentJoystickPos.y = _currentJoystickPos.y * 0.7071;
    }
}
