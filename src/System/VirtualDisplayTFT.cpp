#include "VirtualDisplayTFT.h"

VirtualDisplayTFT::VirtualDisplayTFT(sf::RenderWindow* window) : _window(window) { }

int VirtualDisplayTFT::width() {
    return (int)_window->getSize().x;
}

int VirtualDisplayTFT::height() {
    return (int)_window->getSize().y;
}

void VirtualDisplayTFT::registerShape(int id, VirtualDisplayTFT::GraphicType type) {
    switch (type) {
        case VirtualDisplayTFT::Circle:
            _graphicsMap[id] = new sf::CircleShape();
            break;
        case VirtualDisplayTFT::Rectangle:
            _graphicsMap[id] = new sf::RectangleShape();
            break;
        case VirtualDisplayTFT::BitmapData:
            _graphicsMap[id] = new sf::Sprite();
            break;
        case VirtualDisplayTFT::Text:
            _graphicsMap[id] = new sf::Text();
            break;
        default:
            break;
    }
}

void VirtualDisplayTFT::pixel(int x, int y, int colour) {

}

void VirtualDisplayTFT::circle(int x, int y, int r, int colour) {

}

void VirtualDisplayTFT::fillcircle(int x, int y, int r, int colour) {
    // sf::CircleShape testCircle;
    // testCircle.setRadius(r);
    // testCircle.setPosition(x, y);
    // testCircle.setFillColor(sf::Color::White);
    // _window->draw(testCircle);
    // _window->display();
}

void VirtualDisplayTFT::line(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::rect(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::fillrect(int x0, int y0, int x1, int y1, int colour) {

}

void VirtualDisplayTFT::locate(int x, int y) {

}

void VirtualDisplayTFT::background(uint16_t colour) {
    _background = colour;
}

void VirtualDisplayTFT::cls(void) {
    _window->clear();
}

int VirtualDisplayTFT::_putc(int value) {
    return 0;
}

void VirtualDisplayTFT::character(int x, int y, int c) {

}

void VirtualDisplayTFT::Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) {

}

void VirtualDisplayTFT::set_font(unsigned char *f) {

}

int VirtualDisplayTFT::printf(const char *format, ...) {
    return 0;
}

void VirtualDisplayTFT::set_orientation(unsigned int o) {

}

void VirtualDisplayTFT::circle(int x, int y, int r, int colour, int id) {
    sf::CircleShape* circle = (sf::CircleShape*)_graphicsMap[id];
    circle->setPosition(x, y);
    circle->setRadius(r);
    circle->setOutlineColor(sf::Color::White);
    circle->setFillColor(sf::Color::Black);
    _window->draw(*circle);
    _window->display();
}

void VirtualDisplayTFT::fillcircle(int x, int y, int r, int colour, int id) {
    sf::CircleShape* circle = (sf::CircleShape*)_graphicsMap[id];
    circle->setPosition(x, y);
    circle->setRadius(r);
    circle->setFillColor(sf::Color::White);
    _window->clear();
    _window->draw(*circle);
    _window->display();
}

void VirtualDisplayTFT::clear(int id) {

}
