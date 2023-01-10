#include "GameBase.h"
#include "CollisionHandler.h"

using namespace std::chrono;

GameBase::GameBase(SPI_TFT_ILI9341* tft, InputManager* inputManager) : _tft(tft), _inputManager(inputManager) {
    _timer = new Timer();
    _inputManager->setGame(this);
    _inputManager->setButtonPressedCallback1(&GameBase::handleButtonPressed1);
    _inputManager->setButtonReleasedCallback1(&GameBase::handleButtonReleased1);
    _inputManager->setButtonPressedCallback2(&GameBase::handleButtonPressed2);
    _inputManager->setButtonReleasedCallback2(&GameBase::handleButtonReleased2);
    _inputManager->setJoystickChangedCallback(&GameBase::handleJoystickChanged);
    _inputManager->setCloseRequestCallback(&GameBase::_handleCloseRequest);

    _collisionDelegate = new Delegate<GameBase, Collider::Collision>(this, &GameBase::_handleCollision);
    CollisionHandler::instance().registerCollisionDelegate(_collisionDelegate);
}

GameBase::~GameBase() {
    _run = false;
    _renderThread.join();
    delete _timer;
    delete _collisionDelegate;
}

void GameBase::init() {
    _timer->start();
    _tft->background(BlackTFT);
    _tft->cls();

    setup();

    _renderThread.start(&GameBase::_runRenderQueue, this);
    
    GameObject::drawAll(); // PORTING: remove this in steering version (render queue will handle all rendering)
    _tft->display(); // PORTING: remove this in steering version (render queue will handle all rendering)
}

int GameBase::run() {
    while (_run) {
        // handle input
        _inputManager->run();

        Vec2 curJoystickPos = _inputManager->currentJoystickPos();
        if (curJoystickPos != _lastJoystickPos) {
            handleJoystickChanged(curJoystickPos);
            _lastJoystickPos = curJoystickPos;
        }

        // run 
        int64_t currentTime = millis();
            if (currentTime > _lastFrameMillis + FRAME_RATE_MILLIS) {
                _deltaT = currentTime - _lastFrameMillis;
                
                _tft->clear();  // PORTING: remove this in steering version (render queue will handle all rendering)
                
                CollisionHandler::instance().checkCollisions();
                loop();

                GameObject::drawAll(); // PORTING: remove this in steering version (render queue will handle all rendering)
                _tft->display(); // PORTING: remove this in steering version (render queue will handle all rendering)

                _lastFrameMillis = currentTime;
            }
    }
    return 1;
}

int64_t GameBase::millis() {
    return duration_cast<milliseconds>(_timer->elapsed_time()).count();
}

int64_t GameBase::micros() {
    return duration_cast<microseconds>(_timer->elapsed_time()).count();
}

void GameBase::draw(GameObject* graphic) {
    _renderQueue.push(graphic);
}

void GameBase::_handleCloseRequest() {
    _run = false;
}

void GameBase::_handleCollision(Collider::Collision collision) {
    handleCollision(collision.obj1, collision.obj2, collision.contact);
}

void GameBase::_runRenderQueue() {
    while (_run) {
        while (!_renderQueue.empty()) {
            _renderQueue.front()->clear();
            _renderQueue.front()->draw();
            _renderQueue.pop();
        }
    }
}
