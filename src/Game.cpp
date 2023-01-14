#include "Game.h"

/* Add includes for any graphics/bitmaps you want to use */
#include "Circle.h"
#include "Rectangle.h"
#include "Bitmap.h"
#include "Text.h"
#include "graphics.h"
#include "font_big.h"

#define BALL_SPEED 100
#define BALL_RADIUS 10

#define PADDLE_NAME "paddle"
#define PADDLE_SPEED 175
#define PADDLE_WIDTH 65
#define PADDLE_HEIGHT 65
#define PADDLE_START_X WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2
#define PADDLE_START_Y WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2
#define PADDLE_START util::Point { PADDLE_START_X, PADDLE_START_Y }

/* Declare any global game objects here */
Rectangle* paddle;
Circle* ball1;
Bitmap* bitmap;
Text* text1;
Text* text2;
std::vector<Circle*> balls;

/* Game setup */
void Game::setup() {
    // Initialize any game objects with their start positions here.  Assume that WINDOW_WIDTH
    // and WINDOW_HEIGHT may vary, so try to avoid using hard-coded positions (ie. you should able
    // to play your game on different-sized screens / windows)

    // example code:
    paddle = new Rectangle("paddle", true);
    paddle->init(_tft, PADDLE_START, PADDLE_WIDTH, PADDLE_HEIGHT, BlackTFT, true);
    paddle->setDirection(Vec2 { 0, 0 });
    paddle->setSpeed(PADDLE_SPEED);
    draw(paddle);

    ball1 = new Circle("ball1", true);
    ball1->init(_tft, 60, WINDOW_HEIGHT - 50, GreenTFT, BALL_RADIUS, true);
    ball1->setDirection(Vec2 { -1.9, 1 });
    ball1->setSpeed(BALL_SPEED);
    balls.push_back(ball1);
    draw(ball1);

    bitmap = new Bitmap("bitmap", false);
    bitmap->init(_tft, WINDOW_WIDTH / 2 - SKULL_WIDTH / 2, WINDOW_HEIGHT / 2 - SKULL_HEIGHT / 2, SKULL_WIDTH, SKULL_HEIGHT, (unsigned char*)SkullGraphic);
    draw(bitmap);

    text1 = new Text("text");
    text1->init(_tft, 100, 10, (unsigned char*)Neu42x35, "BALL");
    draw(text1);

    text2 = new Text("text");
    text2->init(_tft, 75, 45, (unsigned char*)Neu42x35, "HERDER");
    draw(text2);
}

void Game::cleanup() {
    delete paddle;
    for (Circle* ball : balls) {
        delete ball;
    }
    
    balls.clear();
    delete bitmap;
    delete text1;
    delete text2;
}

/* Game loop */
void Game::loop() {
    // example
    for (Circle* ball : balls) {
        bool moved = ball->move(_deltaT);

        // Check if each ball is in bounds on X, modify direction vector if it is near edge
        if (ball->getPosition().x - ball->getRadius() < BORDER || 
            ball->getPosition().x + ball->getRadius() > WINDOW_WIDTH - BORDER) {
            // reposition ball so it is within bounds (avoids strange rendering glitchiness)
            if (ball->getPosition().x + ball->getRadius() > WINDOW_WIDTH - BORDER ) {
                ball->setPosition(util::Point { WINDOW_WIDTH - ball->getRadius() - BORDER, ball->getPosition().y });
            } else {
                ball->setPosition(util::Point { ball->getRadius() + BORDER, ball->getPosition().y });
            }
            ball->setDirection(Vec2 { -ball->getDirection().x, ball->getDirection().y });
        }

        // Check if each ball is in bounds on X, modify direction vector if it is near edge
        if (ball->getPosition().y - ball->getRadius() < BORDER ||
            ball->getPosition().y + ball->getRadius() > WINDOW_HEIGHT - BORDER) {
            // reposition ball so it is within bounds (avoids strange rendering glitchiness)
            if (ball->getPosition().y + ball->getRadius() > WINDOW_HEIGHT - BORDER) {
                ball->setPosition(util::Point {  ball->getPosition().x, WINDOW_HEIGHT - ball->getRadius() - BORDER });
            } else {
                ball->setPosition(util::Point { ball->getPosition().x, ball->getRadius() + BORDER });
            }
            ball->setDirection(Vec2 { ball->getDirection().x, -ball->getDirection().y });
        }
        if (moved) {
            draw(ball);
        }
    }

    // move paddle by deltaT
    // (will only move paddle if its direction vector has been set in handle joystick method below)
    if (paddle->move(_deltaT)) {
        draw(paddle);
    }
}

/* Collision event -- params are game objects which have collided, contact is point of collision (on obj1) */
void Game::handleCollision(GameObject* obj1, GameObject* obj2, util::Point& contact) {
    // check if obj1 is paddle
    if (obj1->getName().compare(PADDLE_NAME) == 0 ) {
        if (contact.x == paddle->getPosition().x || contact.x == paddle->getPosition().x + paddle->getWidth()) {
            obj2->setDirection(Vec2 { -obj2->getDirection().x, obj2->getDirection().y });

            // place obj2 outside of paddle to avoid collision loop
            if (contact.x == paddle->getPosition().x) {
                obj2->setPosition(util::Point { contact.x - obj2->getCollider()->getFarthestCollisionDistance(),
                    obj2->getPosition().y });
            } else {
                obj2->setPosition(util::Point { contact.x + obj2->getCollider()->getFarthestCollisionDistance(),
                    obj2->getPosition().y });
            }
        } else {
            obj2->setDirection(Vec2 { obj2->getDirection().x, -obj2->getDirection().y });

            // place obj2 outside of paddle to avoid collision loop
            if (contact.y == paddle->getPosition().y) {
                obj2->setPosition(util::Point { obj2->getPosition().x,
                    contact.y - obj2->getCollider()->getFarthestCollisionDistance() });
            } else {
                obj2->setPosition(util::Point { obj2->getPosition().x,
                    contact.y + obj2->getCollider()->getFarthestCollisionDistance() });
            }
        }
        draw(paddle);
        return;
    }

    // all other objects will simply bounce off of eachother
    Vec2 vec1 = obj1->getDirection();
    Vec2 vec2 = obj2->getDirection();
    obj1->setDirection(Vec2 { vec2.x, vec2.y });
    obj2->setDirection(Vec2 { vec1.x, vec1.y });
}

//////////////////////////////////////////////////
// Input Handlers (keys in sim, actual joystick and steering buttons on Urban steering)
// - see config.h to see or reassign game buttons to different keys

/* Joystick changed event */
void Game::handleJoystickChanged(Vec2 vec) {
    paddle->setDirection(Vec2 { vec.x, vec.y } );
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