#ifndef _VIRTUAL_DISPLAY_TFT_H_
#define _VIRTUAL_DISPLAY_TFT_H_

#include <stdint.h>
#include <unordered_map>
#include "SFML/Graphics.hpp"

#define RGB(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)) // 5 red | 6 green | 5 blue

/* some RGB color definitions                                                 */
#define BlackTFT 0x0000       /*   0,   0,   0 */
#define NavyTFT 0x000F        /*   0,   0, 128 */
#define DarkGreenTFT 0x03E0   /*   0, 128,   0 */
#define DarkCyanTFT 0x03EF    /*   0, 128, 128 */
#define MaroonTFT 0x7800      /* 128,   0,   0 */
#define PurpleTFT 0x780F      /* 128,   0, 128 */
#define OliveTFT 0x7BE0       /* 128, 128,   0 */
#define LightGreyTFT 0xC618   /* 192, 192, 192 */
#define DarkGreyTFT 0x7BEF    /* 128, 128, 128 */
#define BlueTFT 0x001F        /*   0,   0, 255 */
#define GreenTFT 0x07E0       /*   0, 255,   0 */
#define CyanTFT 0x07FF        /*   0, 255, 255 */
#define RedTFT 0xF800         /* 255,   0,   0 */
#define MagentaTFT 0xF81F     /* 255,   0, 255 */
#define YellowTFT 0xFFE0      /* 255, 255,   0 */
#define WhiteTFT 0xFFFF       /* 255, 255, 255 */
#define OrangeTFT 0xFD20      /* 255, 165,   0 */
#define GreenYellowTFT 0xAFE5 /* 173, 255,  47 */

/** 
 *  Virtual display control class which implements graphics-related methods for mbed's SPI_TFT
 */
class VirtualDisplayTFT
{
    public:
        /* Not included in */
        enum GameObjectType { Circle, Rectangle, BitmapData, Text };

        VirtualDisplayTFT(sf::RenderWindow* window);
        ~VirtualDisplayTFT();

        /** Get the width of the window in pixel
         *
         * @returns width of window in pixel
         */
        int width();

        /** Get the height of the window in pixel
         * 
         * @returns height of window in pixel
         */
        int height();

        //////////////////////////////////////////////
        // Not implemented in game sim
        void pixel(int x, int y, int colour);
        void circle(int x, int y, int r, int colour);
        void fillcircle(int x, int y, int r, int colour);
        void line(int x0, int y0, int x1, int y1, int colour);
        void rect(int x0, int y0, int x1, int y1, int colour);
        void fillrect(int x0, int y0, int x1, int y1, int colour);
        void locate(int x, int y);
        int printf(const char *format, ...);
        void set_orientation(unsigned int o);
        int _putc(int value);
        void Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
        void set_font(unsigned char *f);
        //////////////////////////////////////////////

        /** Fill the window with _background color
         *
         */
        void cls(void);
        
        /**
         * Set background colour of window
        */
        void background(uint16_t colour);
        
        /* Not included with firmware TFT API -- do not call directly */
        void registerShape(int id, VirtualDisplayTFT::GameObjectType type);

        /* Not included with firmware TFT API -- do not call directly */
        void circle(int x, int y, int r, int colour, int id);
        
        /* Not included with firmware TFT API -- do not call directly */
        void fillcircle(int x, int y, int r, int colour, int id);

        /* Not included with firmware TFT API -- do not call directly */
        void rect(int x1, int y1, int x2, int y2, int colour, int id);

        /* Not included with firmware TFT API -- do not call directly */
        void fillrect(int x1, int y1, int x2, int y2, int colour, int id);

        /* Not included with firmware TFT API -- do not call directly */
        void Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap, int id);

        /* Not included with firmware TFT API -- do not call directly */
        int printf(const std::string& str, int x, int y, unsigned char* font, int id);

        /* Not included with firmware TFT API -- do not call directly */
        void clear();

        /* Not included with firmware TFT API -- do not call directly */
        void display();

        void bitmapToImage(sf::Image& image, uint8_t* buf, int32_t w, int32_t h);

        static sf::Color convertColor16(int colour);

        static uint16_t computeWidth(const std::string& str, unsigned char* font, uint16_t offset);

    private:
        unsigned char *font;
        sf::RenderWindow* _window;
        uint16_t _background;
        std::unordered_map<int, sf::Drawable*> _graphicsMap;
        std::unordered_map<int, sf::Vector2f*> _sizeMap;
        std::unordered_map<int, sf::Image*> _imageMap;
        std::unordered_map<int, sf::Texture*> _textureMap;
        std::unordered_map<int, bool> _initializedMap;
};

#endif