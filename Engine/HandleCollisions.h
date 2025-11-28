#pragma once
#include "Player.h"
#include "src/core/Map.h"

class HandleCollisions
{
public:
	static HandleCollisions* getInstance();

	int collisions();

private:


	static HandleCollisions* instance;

	HandleCollisions() = default;

	Player* player = nullptr;
	Map* map = nullptr;

};

extern HandleCollisions* manager;