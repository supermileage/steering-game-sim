#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "SFML/Graphics.hpp"
#include "util.h"
#include "GameBase.h"

class GameBase;

using namespace util;

// PORTING: firmware will need its own InputManager
class InputManager {
    public:
        InputManager(sf::RenderWindow* _window);
        ~InputManager() { }
        void init();
        void run();
        void setGame(GameBase* game);
        void setButtonPressedCallback1(void (GameBase::*callback)(void));
        void setButtonReleasedCallback1(void (GameBase::*callback)(void));
        void setButtonPressedCallback2(void (GameBase::*callback)(void));
        void setButtonReleasedCallback2(void (GameBase::*callback)(void));
        void setJoystickChangedCallback(void (GameBase::*callback)(Vec2));
        void setCloseRequestCallback(void (GameBase::*callback)(void));

        /* Returns 'joystick' position with floating point values [-1,1] on x, y */
        Vec2 currentJoystickPos();

    private:
        sf::RenderWindow* _window;
        sf::Event _windowEvent;
        GameBase* _game;
        std::unordered_map<sf::Keyboard::Key, bool> _keyStateMap;
        Vec2 _currentJoystickPos = { 0, 0 };
        void (GameBase::*_pressedCallback1)(void);
        void (GameBase::*_releasedCallback1)(void);
        void (GameBase::*_pressedCallback2)(void);
        void (GameBase::*_releasedCallback2)(void);
        void (GameBase::*_closeRequestCallback)(void);
        void (GameBase::*_joystickCallback)(Vec2);

        void _handleKeyPressed();
        void _handleKeyReleased();
        void _updateJoystick(sf::Keyboard::Key key, sf::Event::EventType type);
};

#endif