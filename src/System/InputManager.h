#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "SFML/Window.hpp"
#include "SystemTypes.h"
#include "Game.h"

class Game;

class InputManager {
    public:
        InputManager(sf::Window* _window);
        ~InputManager() { }
        void init();
        void run();
        void setGame(Game* game);
        void setButtonPressedCallback1(void (Game::*callback)(void));
        void setButtonReleasedCallback1(void (Game::*callback)(void));
        void setButtonPressedCallback2(void (Game::*callback)(void));
        void setButtonReleasedCallback2(void (Game::*callback)(void));
        void setCloseRequestCallback(void (Game::*callback)(void));

        /* Returns 'joystick' position with floating point values [-100,100] on x, y */
        Vec2 currentJoystickPos();

    private:
        sf::Window* _window;
        sf::Event _windowEvent;
        Game* _game;
        Vec2 _currentJoystickPos;
        void (Game::*_pressedCallback1)(void);
        void (Game::*_releasedCallback1)(void);
        void (Game::*_pressedCallback2)(void);
        void (Game::*_releasedCallback2)(void);
        void (Game::*_closeRequestCallback)(void);

        void _handleKeyPressed();
        void _handleKeyReleased();
        void _updateJoystick(sf::Keyboard::Key key, sf::Event::EventType type);
};

#endif