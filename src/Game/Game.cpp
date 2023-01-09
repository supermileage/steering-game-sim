#include "Game.h"

#include <iostream>

/* Add includes for any graphics/bitmaps you want to use */
#include "Circle.h"
#include "Rectangle.h"

#define BALL_SPEED 5
#define BALL_RADIUS 30

#define PADDLE_NAME "paddle"
#define PADDLE_SPEED 10
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 100
#define PADDLE_START_X WINDOW_WIDTH - PADDLE_WIDTH * 4
#define PADDLE_START_Y WINDOW_HEIGHT / 2

/* Declare any global game objects here */
Rectangle* paddle;
Circle* ball1;
Circle* ball2;
std::vector<Circle*> balls;

/* Game setup */
void Game::setup() {
    // Initialize any game objects with their start positions here.  Assume that _tft->width()
    // and _tft->height() may vary, so try to avoid using hard-coded positions (ie. you should able
    // to play your game on different-sized screens / windows)

    // example code:
    // SPI_TFT_ILI9341* tft, int32_t xpos1, int32_t ypos1, int32_t colour, int32_t xpos2, int32_t ypos2, bool fill
    paddle = new Rectangle("paddle", true);
    paddle->init(_tft, PADDLE_START_X - PADDLE_WIDTH, PADDLE_START_Y - PADDLE_HEIGHT, WhiteTFT,
        PADDLE_START_X + PADDLE_WIDTH, PADDLE_START_Y + PADDLE_HEIGHT, true);
    paddle->setDirection(Vec2 { 0, 0 });
    paddle->setSpeed(PADDLE_SPEED);

    ball1 = new Circle("ball1", true);
    ball1->init(_tft, _tft->width() / 2, _tft->height() / 2, WhiteTFT, BALL_RADIUS, true);
    ball1->setDirection(Vec2 { -2.5, -1 });
    ball1->setSpeed(BALL_SPEED);
    balls.push_back(ball1);

    // ball2 = new Circle("ball2", true);
    // ball2->init(_tft, _tft->width() - BALL_RADIUS, _tft->height() / 2, WhiteTFT, BALL_RADIUS, true);
    // ball2->setDirection(Vec2 { 1, -2.5 });
    // ball2->setSpeed(BALL_SPEED);
    // balls.push_back(ball2);
}

void Game::cleanup() {
    for (Circle* ball : balls) {
        delete ball;
    }
    balls.clear();
}

/* Game loop */
void Game::loop() {
    // example
    for (Circle* ball : balls) {
        if (ball->getPosition().x + ball->getRadius() < 0 || 
            ball->getPosition().x + ball->getRadius() > _tft->width()) {
            ball->setDirection(Vec2 { -ball->getDirection().x, ball->getDirection().y });
        }
        if (ball->getPosition().y + ball->getRadius() < 0 ||
            ball->getPosition().y + ball->getRadius() > _tft->height()) {
            ball->setDirection(Vec2 { ball->getDirection().x, -ball->getDirection().y });
        }
        if (ball->move()) {
            draw(ball);
        }
    }

    paddle->move();
    draw(paddle);
}

/* Joystick changed event */
void Game::handleJoystickChanged(Vec2 vec) {
    paddle->setDirection(Vec2 { 0, vec.y } );
}

/* Collision event -- params are game objects which have collided */
void Game::handleCollision(GameObject* obj1, GameObject* obj2) {
    if (obj1->getName().compare(PADDLE_NAME) == 0) {
        obj2->setDirection(Vec2 { -obj2->getDirection().x, obj2->getDirection().y });
        return;
    }
    if (obj2->getName().compare(PADDLE_NAME) == 0) {
        obj1->setDirection(Vec2 { -obj1->getDirection().x, obj1->getDirection().y });
        return;
    }

    Vec2 vec1 = obj1->getDirection();
    Vec2 vec2 = obj2->getDirection();
    obj1->setDirection(Vec2 { vec2.x, vec2.y });
    obj2->setDirection(Vec2 { vec1.x, vec1.y });
}

/* Button 1 pressed event */
void Game::handleButtonPressed1() {
    
}

/* Button 1 released event */
void Game::handleButtonReleased1() {
    
}

/* Button 2 pressed event */
void Game::handleButtonPressed2() {
    
}

/* Button 2 released event */
void Game::handleButtonReleased2() {
    
}