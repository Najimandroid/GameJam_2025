#pragma once
#include "Player.h"
#include "src/core/Map.h"
#include "EntityManager.h"

class HandleCollisions
{
public:
	static HandleCollisions* getInstance();

	int getCollisionSide() { return collisionSide; }

	void collisions();

	bool isGameRunning = true;

private:

	int collisionSide = 0;

	static HandleCollisions* instance;

	HandleCollisions() = default;
};

extern HandleCollisions* managerCollisions;