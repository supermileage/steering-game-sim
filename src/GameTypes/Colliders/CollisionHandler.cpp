#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::_instance = nullptr;

CollisionHandler::CollisionHandler() { }

CollisionHandler& CollisionHandler::instance() {
    if (!_instance) {
        _instance = new CollisionHandler();
    }
    return *_instance;
}

void CollisionHandler::registerCollisionDelegate(util::Command* delegate) {
    _collisionDelegate = delegate;
}

void CollisionHandler::checkCollisions() {
    if (!_collisionDelegate) {
        return;
    }

    const std::vector<Collider*>& allColliders = Collider::allColliders();
    for (int i = 0; i < allColliders.size() - 1; i++) {
        for (int j = i + 1; j < allColliders.size(); j++) {
            _checkCollision(allColliders[i], allColliders[j]);
        }

        if (i == allColliders.size() - 2) {
            break;
        }
    }
}

void CollisionHandler::_checkCollision(Collider* collider1, Collider* collider2) {
	util::Point contact;
    if (collider1->hasCollidedWith(collider2, contact)) {
        Collider::Collision collision(collider1->getOwner(), collider2->getOwner(), contact);
        _collisionDelegate->execute((CommandArgs)&collision);
    }
}

bool CollisionHandler::haveCollided(CircleCollider* circle, RectangleCollider* rectangle, util::Point& contact) {
    util::Point corner1 = rectangle->getPosition();
    util::Point corner2 = util::Point {corner1.x + rectangle->getWidth(), corner1.y + rectangle->getHeight()};
    util::Point topLeft;
    util::Point bottomRight;
    topLeft.x = (corner1.x < corner2.x ? corner1.x : corner2.x);
    bottomRight.x = (corner1.x > corner2.x ? corner1.x : corner2.x);
    topLeft.y = (corner1.y < corner2.y ? corner1.y : corner2.y);
    bottomRight.y = (corner1.y > corner2.y ? corner1.y : corner2.y);

    if (circle->getPosition().x >= topLeft.x - circle->getRadius() &&
		circle->getPosition().x <= bottomRight.x + circle->getRadius()) {
        // side collision
        if (circle->getPosition().y >= topLeft.y && circle->getPosition().y <= bottomRight.y) {
            contact.x = (topLeft.x - circle->getPosition().x > 0) ? topLeft.x : bottomRight.x;
            contact.y = circle->getPosition().y;
			return true;
		}
    }

    if (circle->getPosition().y >= topLeft.y - circle->getRadius() &&
		circle->getPosition().y <= bottomRight.y + circle->getRadius()) {
        // top/bottom collision
        if (circle->getPosition().x >= topLeft.x && circle->getPosition().x <= bottomRight.x) {
            contact.x = circle->getPosition().x;
            contact.y = (topLeft.y - circle->getPosition().y > 0) ? topLeft.y : bottomRight.y;
            return true;
        }
    }
    return false;
}

bool CollisionHandler::haveCollided(CircleCollider* circle1, CircleCollider* circle2, util::Point& contact) {
    if (util::computeDistance(circle1->getPosition(), circle2->getPosition()) <=
        circle1->getRadius() + circle2->getRadius()) {
        util::Vec2 vec = util::Vec2 { static_cast<float>(circle2->getPosition().x - circle1->getPosition().x),
            static_cast<float>(circle2->getPosition().y - circle1->getPosition().y) };
        float magnitude = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
        vec.x = vec.x * (1 / magnitude) * static_cast<float>(circle1->getRadius());
        vec.y = vec.y * (1 / magnitude) * static_cast<float>(circle1->getRadius());
        contact.x = circle1->getPosition().x + round(vec.x);
        contact.y = circle1->getPosition().y + round(vec.y);
        return true;
    }
    return false;
}

bool CollisionHandler::haveCollided(RectangleCollider* rectangle1, RectangleCollider* rectangle2, util::Point& contact) {
    // rectangle 1 top left and bottom right corners
    util::Point corner1 = rectangle1->getPosition();
    util::Point corner2 = util::Point {corner1.x + rectangle1->getWidth(), corner1.y + rectangle1->getHeight()};
    util::Point topLeft1;
    util::Point bottomRight1;
    topLeft1.x = (corner1.x < corner2.x ? corner1.x : corner2.x);
    bottomRight1.x = (corner1.x > corner2.x ? corner1.x : corner2.x);
    topLeft1.y = (corner1.y < corner2.y ? corner1.y : corner2.y);
    bottomRight1.y = (corner1.y > corner2.y ? corner1.y : corner2.y);

    // rectangle 2 top left and bottom right corners
    corner1 = rectangle2->getPosition();
    corner2 = util::Point {corner1.x + rectangle2->getWidth(), corner1.y + rectangle2->getHeight()};
    util::Point topLeft2;
    util::Point bottomRight2;
    topLeft2.x = (corner1.x < corner2.x ? corner1.x : corner2.x);
    bottomRight2.x = (corner1.x > corner2.x ? corner1.x : corner2.x);
    topLeft2.y = (corner1.y < corner2.y ? corner1.y : corner2.y);
    bottomRight2.y = (corner1.y > corner2.y ? corner1.y : corner2.y);
    
    if (util::valueWithinRangeInclusive(topLeft2.x, topLeft1.x - rectangle2->getWidth(), bottomRight1.x)) {
        if (util::valueWithinRangeInclusive(topLeft2.y, topLeft1.y - rectangle2->getHeight(), bottomRight1.y)) {
            if (topLeft2.y >= topLeft1.y && bottomRight2.y <= bottomRight1.y) {
                contact.x = (topLeft2.x < topLeft1.x) ? topLeft1.x : bottomRight1.x;
                contact.y = topLeft2.y;
                return true;
            } else if (topLeft2.x >= topLeft1.x && bottomRight2.x <= bottomRight1.x) {
                contact.x = topLeft2.x;
                contact.y = (topLeft2.y < topLeft1.y) ? topLeft1.y : bottomRight1.y;
                return true;
            } else {
                if (topLeft2.x <= topLeft1.x) {
                    if (bottomRight2.y > bottomRight1.y) {
                        contact.x = topLeft1.x;
                        contact.y = topLeft2.y;
                    } else {
                        contact.x = topLeft1.x;
                        contact.y = topLeft1.y;
                    }
                } else {
                    if (bottomRight2.y >= bottomRight1.y) {
                        contact.x = topLeft2.x;
                        contact.y = bottomRight1.y;
                    } else {
                        contact.x = topLeft2.x;
                        contact.y = topLeft1.y;
                    }
                }
            }
            return true;
        }
    }
    return false;
}
