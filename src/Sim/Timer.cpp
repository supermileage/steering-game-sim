#include "Timer.h"

using namespace std;

void Timer::start() {
    _isRunning = true;
}

void Timer::stop() {
    _isRunning = false;
}

void Timer::reset() {
    if (!_isRunning) {
        _startTime = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch());
    }
}

chrono::microseconds Timer::elapsed_time() const {
    return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()) - _startTime;
}