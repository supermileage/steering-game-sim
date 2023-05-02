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
    /** 
     * Simple rectangle object
    */
    paddle = new Rectangle("paddle", true);
    paddle->init(_tft, PADDLE_START, PADDLE_WIDTH, PADDLE_HEIGHT, PurpleTFT, false);
    paddle->setDirection(Vec2 { 0, 0 });
    paddle->setSpeed(PADDLE_SPEED);
    draw(paddle);

    /** 
     * Simple circle object
    */
    ball1 = new Circle("ball1", true);
    ball1->init(_tft, 60, WINDOW_HEIGHT - 50, GreenTFT, BALL_RADIUS, false);
    ball1->setDirection(Vec2 { -1.9, 1 });
    ball1->setSpeed(BALL_SPEED);
    balls.push_back(ball1);
    draw(ball1);

    /** Create your own graphics by converting images to 16-bit C arrays and loading them into Bitmaps folder
     * 
     * Go to https://lvgl.io/tools/imageconverter to convert them (note: for some reason, images are rendered
     * upside down on urban steering's screen, so you should flip your images before converting to bitmaps)
     * 
     * see graphics.h for examples of how to set this up
     * 
     **/
    bitmap = new Bitmap("bitmap", false);
    bitmap->init(_tft, WINDOW_WIDTH / 2 - SKULL_WIDTH / 2, WINDOW_HEIGHT / 2 - SKULL_HEIGHT / 2, SKULL_WIDTH, SKULL_HEIGHT, (unsigned char*)SkullGraphic);
    draw(bitmap);

    /** See other font options in graphics folder
     *
     * Font size is static, so if you want a different size, you have to
     * create your own bitmap-type font.  There are many options for doing this
     * 
     **/
    text1 = new Text("example_text1");
    text1->init(_tft, 55, 10, (unsigned char*)Neu42x35, "STEERING");
    draw(text1);

    text2 = new Text("example_text2");
    text2->init(_tft, 121, 40, (unsigned char*)Neu42x35, "SIM");
    draw(text2);
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