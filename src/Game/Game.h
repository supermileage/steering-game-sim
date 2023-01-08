#ifndef _GAME_H_
#define _GAME_H_

#include "mbed.h"
#include "config.h"
#include "SPI_TFT_ILI9341.h"
#include "Timer.h"
#include "util.h"
#include "InputManager.h"
#include "ThreadedQueue.h"

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
        Command* _collisionDelegate = nullptr;
        Vec2 _lastJoystickPos = { 0, 0 };
        int64_t _lastFrameMillis = 0;
        int64_t _deltaT = 0;
        bool _run = true;
        Thread _renderThread;
        ThreadedQueue<Graphic*> _renderQueue;

        /* Primary Game API */
        void setup();
        void cleanup();
        void loop();
        void handleJoystickChanged(Vec2 vec);
        void handleCollision(const std::string& obj1, const std::string& obj2);
        void handleButtonPressed1();
        void handleButtonReleased1();
        void handleButtonPressed2();
        void handleButtonReleased2();
        int64_t millis();
        int64_t micros();
        void draw(Graphic* graphic);

        void _handleCloseRequest();
        void _handleCollision(util::Collision collision);
        void _runRenderQueue();
};

#endif