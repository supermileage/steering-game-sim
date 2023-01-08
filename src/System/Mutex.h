#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <mutex>

class Mutex {
    public:
        void lock() {
            _actualMutex.lock();
        }

        void unlock() {
            _actualMutex.unlock();
        }

    private:
        std::mutex _actualMutex;
};

#endif