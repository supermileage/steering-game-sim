#ifndef _MOCK_GAME_OBJECT_H_
#define _MOCK_GAME_OBJECT_H_

#include "GameObject.h"

class MockGameObject : public GameObject {
	public:
		MockGameObject(std::string name = "", bool enableCollisions = false) : 
			GameObject(name, enableCollisions) { }
		void draw() override { }
		void clear() override { }
};

#endif