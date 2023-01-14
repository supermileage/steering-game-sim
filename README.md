# Urban Steering Game Simulator

<img src="https://github.com/supermileage/steering-game-sim/blob/main/media/Example_PC.png" width="500">

Simulator to develop games which will run on urban steering wheel screen

## API

Game functions closely resemble Arduino API:

```C++
void setup();
void loop();
```

With the addition of input event handlers and a teardown function to free any dynamically allocated memory:

```C++
// for teardown
void cleanup();

// joystick input handler where vec is the direction of the joystick
void handleJoystickChanged(Vec2 vec);

// button input handlers (only two buttons to keep things simple)
void handleButtonPressed1();
void handleButtonReleased1();
void handleButtonPressed2();
void handleButtonReleased2();
```

And a function which will be called if two game objects collide:
```C++
// handle collision event, where obj1 and obj2 are the game objects which have collided
// contact is the x,y point at which they have collided
void handleCollision(GameObject* obj1, GameObject* obj2, util::Point& contact) override;
```

There is much more documentation in the comments of src/Game.cpp!

## Examples

There is an example game project on example_game branch which you can check out to get an idea of how to use the API (sim rendering pictured above).  

### Here is what it looks like on urban steering:

<img src="https://github.com/supermileage/steering-game-sim/blob/main/media/Example_Steering.jpg" width="450">

## Important!
There are some discrepancies between how the game will look and perform in the game sim vs urban steering itself:

Urban steering has to run the game on a microcontroller which is powerful, but relatively powerful wimpy compared to the CPU/GPU combo which you will no doubt run the game sim on.  If you are going to make a game, you can include fairly sophisticated logic, but you CANNOT render more than 2 objects per frame without significantly lowering the framerate of the game.  This means that complex physics-based games are not really possible, unless they are about as simple as Pong.

Also, because of the way the ILI9341 renders objects, overlapping objects will delete eachother's pixels.  This will not be apparent in the game sim.  I will include some example pictures here eventually to show what this looks like.  Best practice for your game would be to avoid any significantly overlapping shapes.

## Dependencies:
SFML libraries must be installed to run the game on macOS, linux, and windows

For instructions on how to install, go to the [SFML website](https://www.sfml-dev.org/)
