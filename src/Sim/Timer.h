#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer {
    public:
        /** Start the timer
         */
        void start();

        /** Stop the timer
         */
        void stop();

        /** Reset the timer to 0.
         *
         * If it was already running, it will continue
         */
        void reset();

        /** Get in a high resolution type the time passed in microseconds.
         *  Returns a 64 bit integer chrono duration
         */
        std::chrono::microseconds elapsed_time() const;

    private:
        std::chrono::microseconds _startTime;
        bool _isRunning = false;
};



    #endif