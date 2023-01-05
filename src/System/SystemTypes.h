#ifndef _SYSTEM_TYPES_H_
#define _SYSTEM_TYPES_H_

struct Vec2 {
    float x;
    float y;

    bool operator!=(Vec2 vec) {
        return x != vec.x || y != vec.y;
    }
};

#endif