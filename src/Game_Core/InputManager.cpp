#include "config.h"
#include "InputManager.h"

#include <iostream>

InputManager::InputManager(sf::RenderWindow* window) : _window(window) { }

void InputManager::init() {
    _keyStateMap[BUTTON_1] = false;
    _keyStateMap[BUTTON_2] = false;
    _keyStateMap[sf::Keyboard::Up] = false;
    _keyStateMap[sf::Keyboard::Down] = false;
    _keyStateMap[sf::Keyboard::Left] = false;
    _keyStateMap[sf::Keyboard::Right] = false;
}

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

void InputManager::setGame(GameBase* game) {
    _game = game;
}

void InputManager::setButtonPressedCallback1(void (GameBase::*callback)(void)) {
    _pressedCallback1 = callback;
}

void InputManager::setButtonReleasedCallback1(void (GameBase::*callback)(void)) {
    _releasedCallback1 = callback;
}

void InputManager::setButtonPressedCallback2(void (GameBase::*callback)(void)) {
    _pressedCallback2 = callback;
}

void InputManager::setButtonReleasedCallback2(void (GameBase::*callback)(void)) {
    _releasedCallback2 = callback;
}

void InputManager::setCloseRequestCallback(void (GameBase::*callback)(void)) {
    _closeRequestCallback = callback;
}

void InputManager::setJoystickChangedCallback(void (GameBase::*callback)(Vec2)) {
    _joystickCallback = callback;
}

Vec2 InputManager::currentJoystickPos() {
    return Vec2 { 0, 0 };
}

void InputManager::_handleKeyPressed() {
    if (_keyStateMap[_windowEvent.key.code]) {
        return;
    }

    _keyStateMap[_windowEvent.key.code] = true;

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
    if (!_keyStateMap[_windowEvent.key.code]) {
        return;
    }

    _keyStateMap[_windowEvent.key.code] = false;

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
                _currentJoystickPos.y = -1;
            } else {
                _currentJoystickPos.y = (_currentJoystickPos.y > 0 ? 1 : 0);
            }
            break;
        case sf::Keyboard::Down:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.y = 1;
            } else {
                _currentJoystickPos.y = (_currentJoystickPos.y < 0 ? -1 : 0);
            }
            break;
        case sf::Keyboard::Left:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.x = -1;
            } else {
                _currentJoystickPos.x = (_currentJoystickPos.x > 0 ? 1 : 0);
            }
            break;
        case sf::Keyboard::Right:
            if (type == sf::Event::KeyPressed) {
                _currentJoystickPos.x = 1;
            } else {
                _currentJoystickPos.x = (_currentJoystickPos.x < 0 ? -1 : 0);
            }
            break;
        default:
            break;
    }

    // check if Vec2 should be 45°
    if (_currentJoystickPos.x != 0 && _currentJoystickPos.y != 0) {
        _currentJoystickPos.x = (_currentJoystickPos.x < 0 ? -0.7071 : 0.7071);
        _currentJoystickPos.y = (_currentJoystickPos.y < 0 ? -0.7071 : 0.7071);
    }

    (_game->*_joystickCallback)(_currentJoystickPos);
}
