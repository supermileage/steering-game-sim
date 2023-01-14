#include "Game.h"

/* Add includes for any graphics/bitmaps you want to use */
#include "Circle.h"
#include "Rectangle.h"
#include "Bitmap.h"
#include "Text.h"
#include "graphics.h"
#include "font_big.h"

/* Macros */
#define BALL_RADIUS 10
#define BALL_SPEED 40
#define SPEED_CHANGE 10

/* Declare any game objects here */
Circle* ball; // example

/** Game setup
 * 
 * Initialize any game objects with their start positions here.  Assume that WINDOW_WIDTH
 * and WINDOW_HEIGHT may vary, so try to avoid using hard-coded positions (ie. you should able
 * to play your game on different-sized screens / windows)
 * 
 **/
void Game::setup() {
    // example
    ball = new Circle("ball", true);
    // initialize at x,y with colour: green, radius: BALL_RADIUS and no colour fill (outline)
    ball->init(_tft, BALL_RADIUS + 5, WINDOW_HEIGHT / 2, GreenTFT, BALL_RADIUS, false);
    //set ball's velocity (in pixels per second)
    ball->setSpeed(BALL_SPEED);
    // set direction vector for ball
    ball->setDirection(util::Vec2 { 1.7, -0.2 });
    // draw ball on screen
    draw(ball);
}

/** Cleanup
 * 
 * Delete any dynamically allocated memory:
 * (call delete on all objects instantiated with 'new')
 * 
 **/
void Game::cleanup() {
    delete ball;
}

/** Core Game loop
 * 
 * Called once per FRAME_RATE_MILLIS (defined in Game_Core/GameBase.h)
 * 
 **/
void Game::loop() {
    // try moving the ball -- _deltaT is the time since last frame
    if (ball->move(_deltaT)) {
        // draw ball if it has been moved
        draw(ball);
    }
}

/** Collision event
 *
 * this will be called if the collider objects of two game objects overlap
 * 
 * @param obj1 the first game object involved in the collision
 * @param obj2 the second game object involved in the collision
 * @param contact the exact point of the collision (on the perimeter of obj1)
 * 
 */
void Game::handleCollision(GameObject* obj1, GameObject* obj2, util::Point& contact) {
    
}

/////////////////////////////////////////////////////////////////////
// Input Handlers (keys in sim, actual joystick and steering buttons on Urban steering)
// see config.h to see or reassign game buttons to different keys

/** Joystick Changed Event
 *
 * Simulates urban joystick input:
 * Called when you press arrow keys on keyboard
 * 
 * @param vec a vector representing the x,y direction of the 'joystick'
 * 
 **/
void Game::handleJoystickChanged(Vec2 vec) {
    // change direction of ball based on input
    ball->setDirection(vec);
}

/* Button 1 pressed event */
void Game::handleButtonPressed1() {
    // increase ball speed by pressing button 1
    ball->setSpeed(ball->getSpeed() + SPEED_CHANGE);
}

/* Button 1 released event */
void Game::handleButtonReleased1() {
    
}

/* Button 2 pressed event */
void Game::handleButtonPressed2() {
    // decrease ball speed by pressing button 2
    ball->setSpeed(ball->getSpeed() - SPEED_CHANGE);
}

/* Button 2 released event */
void Game::handleButtonReleased2() {
    
}