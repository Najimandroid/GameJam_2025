#pragma once
#include "../entities/Player.h"
#include "../Map.h"
#include "EntityManager.h"

class HandleCollisions
{
public:
	static HandleCollisions* getInstance();

	std::vector<int>& getCollisionSides() { return collisionSides; }

	void collisions();

	bool isGameRunning = true;

private:
	std::vector<int> collisionSides;

	static HandleCollisions* instance;

	HandleCollisions() = default;
};

extern HandleCollisions* managerCollisions;