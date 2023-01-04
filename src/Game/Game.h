#include "SPI_TFT_ILI9341.h"
#include "Timer.h"

/* Add includes for any graphics/bitmaps you want to use */
#include "Circle.h"

class Game {
    public:
        Game(SPI_TFT_ILI9341* tft);
        ~Game();

        /* Initialize game objects here */
        void init();

        /* Define game behavior here */
        void run();

    private:
        SPI_TFT_ILI9341* _tft;
        Timer* _timer;
        bool _run = true;

        /* Declare game objects here */
        // Circle* _ball;
};