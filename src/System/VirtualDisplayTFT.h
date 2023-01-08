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

/** Display control class which implements graphics-related methods for mbed's SPI_TFT
 *
 * Example:
 *
 * #include <string>
 * #include "VirtualDisplayTFT.h"
 * #include "Arial12x12.h"
 * #include "Arial24x23.h"
 *
 * int main() {
 *     VirtualDisplayTFT TFT(200, 200); 
 *     TFT.background(BlackTFT);    // set background to black
 *     TFT.foreground(White);    // set chars to white
 *     TFT.cls();                // clear the window
 *     TFT.set_font((unsigned char*) Arial12x12);  // select the font
 *
 *     TFT.set_orientation(0);
 *     printf("  Hello World 0");
 *     TFT.set_font((unsigned char*) Arial24x23);  // select font 2
 *     TFT.locate(75,100);
 *     TFT.printf("Bigger Font");
 *  }

 */
class VirtualDisplayTFT
{
    public:
        /* Not included in */
        enum GraphicType { Circle, Rectangle, BitmapData, Text };

        VirtualDisplayTFT(sf::RenderWindow* window);

        /** Get the width of the window in pixel
         *
         * @returns width of window in pixel
         *
         */
        int width();

        /** Get the height of the window in pixel
         *
         * @returns height of window in pixel
         *
         */
        int height();

        /** Draw a pixel at x,y with color
         *
         * @param x horizontal position
         * @param y vertical position
         * @param color 16 bit pixel color
         */
        void pixel(int x, int y, int colour);

        /** draw a circle
         *
         * @param x0,y0 center
         * @param r radius
         * @param color 16 bit color                                                                 *
         *
         */
        void circle(int x, int y, int r, int colour);

        /** draw a filled circle
         *
         * @param x0,y0 center
         * @param r radius
         * @param color 16 bit color                                                                 *
         */
        void fillcircle(int x, int y, int r, int colour);

        /** draw a 1 pixel line
         *
         * @param x0,y0 start point
         * @param x1,y1 stop point
         * @param color 16 bit color
         *
         */
        void line(int x0, int y0, int x1, int y1, int colour);

        /** draw a rect
         *
         * @param x0,y0 top left corner
         * @param x1,y1 down right corner
         * @param color 16 bit color
         *                                                   *
         */
        void rect(int x0, int y0, int x1, int y1, int colour);

        /** draw a filled rect
         *
         * @param x0,y0 top left corner
         * @param x1,y1 down right corner
         * @param color 16 bit color
         *
         */
        void fillrect(int x0, int y0, int x1, int y1, int colour);

        /** setup cursor position
         *
         * @param x x-position (top left)
         * @param y y-position
         */
        void locate(int x, int y);

        void background(uint16_t colour);

        /** Fill the window with _background color
         *
         */
        void cls(void);

        /** put a char on the window
         *
         * @param value char to print
         * @returns printed char
         *
         */
        int _putc(int value);

        /** draw a character on given position out of the active font to the TFT
         *
         * @param x x-position of char (top left)
         * @param y y-position
         * @param c char to print
         *
         */
        virtual void character(int x, int y, int c);

        /** paint a bitmap on the TFT
         *
         * @param x,y : upper left corner
         * @param w width of bitmap
         * @param h high of bitmap
         * @param *bitmap pointer to the bitmap data
         */
        void Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);

        /** select the font to use
         *
         * @param f pointer to font array
         *
         *   font array can created with GLCD Font Creator from http://www.mikroe.com
         *   you have to add 4 parameter at the beginning of the font array to use:
         *   - the number of byte / char
         *   - the vertial size in pixel
         *   - the horizontal size in pixel
         *   - the number of byte per vertical line
         *   you also have to change the array to char[]
         *
         */
        void set_font(unsigned char *f);

        /*
         * Prints character to window
        */
        int printf(const char *format, ...);

        /** Set the orientation of the window
         *  x,y: 0,0 is always top left
         *
         * @param o direction to use the window (0-3)
         *
         */
        void set_orientation(unsigned int o);
        
        /* Method below is not included in firmware TFT object -- do not use */
        void registerShape(int id, VirtualDisplayTFT::GraphicType type);

        /* Method below is not included in firmware TFT object -- do not use */
        void circle(int x, int y, int r, int colour, int id);
        
        /* Method below is not included in firmware TFT object -- do not use */
        void fillcircle(int x, int y, int r, int colour, int id);

        /* Method below is not included in firmware TFT object -- do not use */
        void clear();

        void display();


    private:
        unsigned char *font;
        sf::RenderWindow* _window;
        uint16_t _background;
        std::unordered_map<int, sf::Drawable*> _graphicsMap;
};

#endif