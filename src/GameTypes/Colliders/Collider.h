#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <vector>

#include "util.h"
#include "GameObject.h"

class GameObject;

class Collider {
    public:
        enum ColliderType { Circle, Rectangle };
        Collider(GameObject* owner);
        virtual ~Collider();
        util::Point getPosition();
        GameObject* getOwner();
        ColliderType getType();
        bool hasCollidedWith(Collider* collider);
        virtual int32_t getFarthestCollisionDistance() = 0;
        static const std::vector<Collider*>& allColliders();

    protected:
        GameObject* _owner;
        Collider::ColliderType _type;

        bool _withinCollisionRange(Collider* collider);
        virtual bool _hasCollidedWith(Collider* collider) = 0;

    private:
        static std::vector<Collider*> _allColliders;
};

#endif