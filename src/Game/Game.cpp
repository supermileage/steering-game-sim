#include "Game.h"

#include <iostream>

#define BALL_SPEED 10
#define BALL_RADIUS 40

/* Declare any game objects here */
Circle* ball1; // example
Circle* ball2; // example
Circle* ball3; // example
std::vector<Circle*> balls;

/* Game setup */
void Game::setup() {
    // Initialize any game objects with their start positions here.  Assume that _tft->width()
    // and _tft->height() may vary, so try to avoid using hard-coded positions (ie. you should able
    // to play your game on different-sized screens / windows)

    // example code:
    ball1 = new Circle("ball1", true);
    ball1->init(_tft, BALL_RADIUS, _tft->height() - BALL_RADIUS, WhiteTFT, BALL_RADIUS, true);
    ball1->setDirection(Vec2 { 2.5, -1 });
    ball1->setSpeed(BALL_SPEED);
    balls.push_back(ball1);

    ball2 = new Circle("ball2", true);
    ball2->init(_tft, _tft->width() / 2, _tft->height() / 2, WhiteTFT, BALL_RADIUS, true);
    ball2->setDirection(Vec2 { -2.5, -1 });
    ball2->setSpeed(BALL_SPEED);
    balls.push_back(ball2);

    ball3 = new Circle("ball3", true);
    ball3->init(_tft, _tft->width() / 2, _tft->height() / 2, WhiteTFT, BALL_RADIUS, true);
    ball3->setDirection(Vec2 { 1, -2.5 });
    ball3->setSpeed(BALL_SPEED);
    balls.push_back(ball3);
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
}

/* Joystick changed event */
void Game::handleJoystickChanged(Vec2 vec) {
    // example
    ball1->setDirection(vec);
}

/* Collision event -- strings are names of Graphic objects which have collided */
void Game::handleCollision(const std::string& obj1, const std::string& obj2) {
    std::cout << "Collision! obj1 = " << obj1 << " , obj2 = " << obj2 << std::endl;
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