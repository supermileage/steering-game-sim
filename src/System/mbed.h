#ifndef _MBED_H_
#define _MBED_H_

#include <thread>
#include <iostream>

class Thread {
    public:
        ~Thread() {
            // _thread->join();
            // delete _thread;
        }

        template <typename T>
        void start(void (T::*method)(void), T* object) {
            // _thread = new std::thread(method, object);
            // _thread->detach();
        }

        void join() {
            // _thread->join();
        }
    
    private:
        std::thread* _thread;
};

#endif