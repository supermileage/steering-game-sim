#ifndef _STEERING_GRAPHIC_H_
#define _STEERING_GRAPHIC_H_

#include <vector>
#include <string>

#include "Shape.h"
#include "util.h"

using namespace util;

class Graphic : public Shape {
    public:
        Graphic(std::string name, bool enableCollision);
        virtual ~Graphic();
        const std::string& getName();
        void setDirection(Vec2 dir);
		Vec2 getDirection();
		void setSpeed(int32_t speed);
		int32_t getSpeed();
        void setPosition(Pos pos);
        Pos getPosition();
        void setEnableCollisions(bool enable);
        /* Returns true if position has been updated */
		bool move();

        bool hasCollidedWith(Graphic* graphic);
        virtual int32_t getFarthestPixelDistance() = 0;
        static void checkCollisions();
        static void registerCollisionDelegate(Command* delegate);
        static void drawAll(); // PORTING: remove this method and all references

    protected:
        static int id;
        int _id;
        Vec2 _direction = { 0, 0 };
        std::string _name;
		int32_t _speed = 0;
        float _lastDeltaX = 0;
        float _lastDeltaY = 0;
        bool _enableCollisions;

    private:
        class CollidableGraphics {
            public:
                void add(Graphic* graphic);
                void remove(Graphic* graphic);
                void checkCollisions();
                void registerCollisionDelegate(Command* delegate);

            private:
                std::vector<Graphic*> _graphics;
                Command* _collisionDelegate = nullptr;
        };

        static CollidableGraphics _collidableGraphics;
        static std::vector<Graphic*> _allGraphics; // PORTING: remove this and all references

        bool _withinCollisionRange(Graphic* graphic);
        virtual bool _hasCollidedWith(Graphic* graphic) = 0;
};

#endif