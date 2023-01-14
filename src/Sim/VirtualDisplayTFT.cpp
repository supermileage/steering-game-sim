#include <iostream>
#include <string.h>

#include "VirtualDisplayTFT.h"

VirtualDisplayTFT::VirtualDisplayTFT(sf::RenderWindow* window) : _window(window) { }

VirtualDisplayTFT::~VirtualDisplayTFT() {
    for (auto const& pair : _graphicsMap) {
        delete pair.second;
    }
    for (auto const& pair : _sizeMap) {
        delete pair.second;
    }
    for (auto const& pair : _textureMap) {
        delete pair.second;
    }
    for (auto const& pair : _imageMap) {
        delete pair.second;
    }
}

int VirtualDisplayTFT::width() {
    return (int)_window->getSize().x;
}

int VirtualDisplayTFT::height() {
    return (int)_window->getSize().y;
}

void VirtualDisplayTFT::registerShape(int id, VirtualDisplayTFT::GameObjectType type) {
    switch (type) {
        case VirtualDisplayTFT::Circle:
            _graphicsMap[id] = new sf::CircleShape();
            break;
        case VirtualDisplayTFT::Rectangle:
            _graphicsMap[id] = new sf::RectangleShape();
            _sizeMap[id] = new sf::Vector2f(0, 0);
            break;
        case VirtualDisplayTFT::BitmapData:
            _graphicsMap[id] = new sf::Sprite();
            _textureMap[id] = new sf::Texture();
            _imageMap[id] = new sf::Image();
            _initializedMap[id] = false;
            break;
        case VirtualDisplayTFT::Text:
            _graphicsMap[id] = new sf::Sprite();
            _textureMap[id] = new sf::Texture();
            _imageMap[id] = new sf::Image();
            break;
        default:
            break;
    }
}

// Not implemented in virtual tft class
void VirtualDisplayTFT::pixel(int x, int y, int colour) { }
void VirtualDisplayTFT::circle(int x, int y, int r, int colour) { }
void VirtualDisplayTFT::fillcircle(int x, int y, int r, int colour) { }
void VirtualDisplayTFT::line(int x0, int y0, int x1, int y1, int colour) { }
void VirtualDisplayTFT::rect(int x0, int y0, int x1, int y1, int colour) { }
void VirtualDisplayTFT::fillrect(int x0, int y0, int x1, int y1, int colour) { }
void VirtualDisplayTFT::locate(int x, int y) { }
void VirtualDisplayTFT::Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) { }
void VirtualDisplayTFT::set_font(unsigned char *f) { }
int VirtualDisplayTFT::printf(const char *format, ...) { return 0; }
void VirtualDisplayTFT::set_orientation(unsigned int o) { }

void VirtualDisplayTFT::background(uint16_t colour) {
    _background = colour;
}

void VirtualDisplayTFT::cls(void) {
    _window->clear();
}

int VirtualDisplayTFT::_putc(int value) {
    return 0;
}

void VirtualDisplayTFT::circle(int x, int y, int r, int colour, int id) {
    sf::CircleShape* circle = (sf::CircleShape*)_graphicsMap[id];
    circle->setPosition(x, y);
    circle->setRadius(r);
    circle->setOutlineThickness(5);
    circle->setOutlineColor(VirtualDisplayTFT::convertColor16(colour));
    _window->draw(*circle);
}

void VirtualDisplayTFT::fillcircle(int x, int y, int r, int colour, int id) {
    sf::CircleShape* circle = (sf::CircleShape*)_graphicsMap[id];
    circle->setPosition(x, y);
    circle->setOrigin(r, r);
    circle->setRadius(r);
    circle->setFillColor(VirtualDisplayTFT::convertColor16(colour));
    _window->draw(*circle);
}

void VirtualDisplayTFT::rect(int x1, int y1, int x2, int y2, int colour, int id) {
    sf::RectangleShape* rectangle = (sf::RectangleShape*)_graphicsMap[id];
    int width = x2 - x1;
    int height = y2 - y1;
    rectangle->setPosition(x1, y1);
    sf::Vector2f* sizeVec = _sizeMap[id];
    sizeVec->x = width;
    sizeVec->y = height;
    rectangle->setSize(*sizeVec);
    rectangle->setOutlineThickness(5);
    rectangle->setOutlineColor(VirtualDisplayTFT::convertColor16(colour));
    _window->draw(*rectangle);
}

void VirtualDisplayTFT::fillrect(int x1, int y1, int x2, int y2, int colour, int id) {
    sf::RectangleShape* rectangle = (sf::RectangleShape*)_graphicsMap[id];
    int width = x2 - x1;
    int height = y2 - y1;
    rectangle->setPosition(x1, y1);
    sf::Vector2f* sizeVec = _sizeMap[id];
    sizeVec->x = width;
    sizeVec->y = height;
    rectangle->setSize(*sizeVec);
    rectangle->setFillColor(VirtualDisplayTFT::convertColor16(colour));
    _window->draw(*rectangle);
}

void VirtualDisplayTFT::Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap, int id) {
    sf::Sprite* sprite = (sf::Sprite*)_graphicsMap[id];

    if (!_initializedMap[id]) {
        sf::Image&  image = *_imageMap[id];
        image.create(w, h, sf::Color::Black);
        bitmapToImage(image, bitmap, w, h);
        sf::Texture& texture = *_textureMap[id];
        bool success = texture.loadFromImage(image);

        if (!success) {
            std::cout << "Failed to load texture from image!" << std::endl;
            return;
        }

        sprite->setTexture(texture);
        sprite->setPosition(x, y);
        sprite->setScale(1, 1);
    }

    _window->draw(*sprite);
}

int VirtualDisplayTFT::printf(const std::string& str, int x, int y, unsigned char* font, int id) {
    uint16_t offset = (uint16_t)font[0];
    uint16_t w = computeWidth(str, font + 4, offset);
    uint16_t h = (uint16_t)font[2];
    uint16_t bytesPerColumn = (uint16_t)font[3];
    font += 4;

    sf::Image& image = *_imageMap[id];
    image.create(w, h);
    
    uint16_t cur_x = 0;
    for (int i = 0; i < str.size();i++) {
        uint8_t cur = (uint8_t)str[i] - 32;
        uint16_t cur_columns = (uint8_t)font[cur * offset];
        uint8_t* cur_bitmap = (uint8_t*)(font + cur * offset + 1);

        for (uint16_t x1 = 0; x1 < cur_columns; x1++) {
            // draw a column of pixels
            for (int16_t j = 0; j < bytesPerColumn; j++) {
                uint8_t b = cur_bitmap[x1 * bytesPerColumn + j];

                for (uint16_t k = 0; k < 8; k++) {
                    uint8_t y1 = j * 8 + k;
                    if (y1 >= h) {
                        break;
                    }
                    if ((b >> k) & 0x1) {
                        image.setPixel(cur_x + x1, y1, sf::Color::White);
                    } else {
                        image.setPixel(cur_x + x1, y1, sf::Color::Transparent);
                    }
                }
            }
        }
        cur_x += cur_columns;
    }

    sf::Texture& texture = *_textureMap[id];
    bool success = texture.loadFromImage(image);

    if (!success) {
        std::cout << "Failed to load texture from image!" << std::endl;
        return -1;
    }

    sf::Sprite* sprite = (sf::Sprite*)_graphicsMap[id];
    sprite->setTexture(texture);
    sprite->setPosition(x, y);
    _window->draw(*sprite);
    return 1;
}

void VirtualDisplayTFT::clear() {
    _window->clear();
}

void VirtualDisplayTFT::display() {
    _window->display();
}

void VirtualDisplayTFT::bitmapToImage(sf::Image& image, uint8_t* buf, int32_t w, int32_t h) {
    for (int32_t y = 0; y < h; y++) {
        for (int32_t x = 0; x < w; x++) {
            image.setPixel(x, y, convertColor16(*(uint16_t*)(buf + x * 2 + y * w * 2)));
        }
    }
}

sf::Color VirtualDisplayTFT::convertColor16(int colour) {
    uint8_t r = (uint8_t)(colour >> 11) * 8;
    uint8_t g = ((uint8_t)(colour >> 5) & 0x3F) * 4;
    uint8_t b = (uint8_t)(colour & 0x1F) * 8;
    return sf::Color(r, g, b);
}

sf::Color VirtualDisplayTFT::convertColor8(int colour) {
    uint8_t r = (uint8_t)(colour >> 5) * 32;
    uint8_t g = ((uint8_t)(colour >> 2) & 0x7) * 32;
    uint8_t b = (uint8_t)(colour & 0x3) * 64;
    return sf::Color(r, g, b);
}

uint16_t VirtualDisplayTFT::computeWidth(const std::string& str, unsigned char* font, uint16_t offset) {
    uint16_t ret = 0;
    for (uint16_t i = 0; i < str.size(); i++) {
        ret += (uint16_t)font[(str[i] - 32) * offset];
    }
    return ret;
}
