#ifndef _GAME_H_
#define _GAME_H_

#include "SPI_TFT_ILI9341.h"
#include "Timer.h"
#include "SystemTypes.h"
#include "InputManager.h"

/* Add includes for any graphics/bitmaps you want to use */
#include "Circle.h"

class InputManager;

class Game {
    public:
        Game(SPI_TFT_ILI9341* tft, InputManager* _inputManager);
        ~Game();
        void init();
        int run();

    private:
        SPI_TFT_ILI9341* _tft;
        Timer* _timer;
        InputManager* _inputManager;
        Vec2 _lastJoystickPos = { 0, 0 };
        bool _run = true;
        /* Declare any game objects here */
        Circle* _ball; // example object

        void _loop();
        void _handleJoystickChanged(Vec2 pos);
        void _handleButtonPressed1();
        void _handleButtonReleased1();
        void _handleButtonPressed2();
        void _handleButtonReleased2();
        int64_t _millis();
        int64_t _micros();

        void _handleCloseRequest();
};

#endif