#ifndef _STEERING_GRAPHIC_H_
#define _STEERING_GRAPHIC_H_

#include "Shape.h"
#include "SystemTypes.h"

class Graphic : public Shape {
    public:
        Graphic();
        virtual ~Graphic() { }
        void setDirection(Vec2 dir);
		Vec2 getDirection();
		void setSpeed(int32_t speed);
		int32_t getSpeed();
		void move();

    protected:
        static int id;
        int _id;
        Vec2 _direction = { 0, 0 };
		int32_t _speed = 0;
        float _lastDeltaX = 0;
        float _lastDeltaY = 0;
};

#endif