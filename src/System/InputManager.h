#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "SFML/Graphics.hpp"
#include "util.h"
#include "Game.h"

class Game;

using namespace util;

class InputManager {
    public:
        InputManager(sf::RenderWindow* _window);
        ~InputManager() { }
        void init();
        void run();
        void setGame(Game* game);
        void setButtonPressedCallback1(void (Game::*callback)(void));
        void setButtonReleasedCallback1(void (Game::*callback)(void));
        void setButtonPressedCallback2(void (Game::*callback)(void));
        void setButtonReleasedCallback2(void (Game::*callback)(void));
        void setJoystickChangedCallback(void (Game::*callback)(Vec2));
        void setCloseRequestCallback(void (Game::*callback)(void));

        /* Returns 'joystick' position with floating point values [-1,1] on x, y */
        Vec2 currentJoystickPos();

    private:
        sf::RenderWindow* _window;
        sf::Event _windowEvent;
        Game* _game;
        std::unordered_map<sf::Keyboard::Key, bool> _keyStateMap;
        Vec2 _currentJoystickPos = { 0, 0 };
        void (Game::*_pressedCallback1)(void);
        void (Game::*_releasedCallback1)(void);
        void (Game::*_pressedCallback2)(void);
        void (Game::*_releasedCallback2)(void);
        void (Game::*_closeRequestCallback)(void);
        void (Game::*_joystickCallback)(Vec2);

        void _handleKeyPressed();
        void _handleKeyReleased();
        void _updateJoystick(sf::Keyboard::Key key, sf::Event::EventType type);
};

#endif