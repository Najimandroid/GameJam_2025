#include "HandleCollisions.h"


HandleCollisions* HandleCollisions::getInstance()
{
	if (instance == nullptr) { instance = new HandleCollisions(); }
	return instance;
}




int HandleCollisions::collisions()
{
	for (auto wall : map->GetCollisionBounds()) {
		if (sf::FloatRect({ player->getHB().position.x , player->getHB().position.y + player->getHB().size.y - 1 }, { player->getHB().size.x,1 }).findIntersection(wall))
		{
			return 1; //Collision Bot
		}
		if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, { player->getHB().size.x, 1 }).findIntersection(wall))
		{
			return 2; //Collision Top
		}
		if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, {1, player->getHB().size.y}).findIntersection(wall))
		{
			return 3; //Collision Left
		}
		if (sf::FloatRect({player->getHB().position.x + player->getHB().size.x, player->getHB().position.y}, {1, player->getHB().size.y}).findIntersection(wall)) {
			return 4; //Collision Right
		}
	}
	return 0;
}

HandleCollisions* HandleCollisions::instance = nullptr;
HandleCollisions* manager = HandleCollisions::getInstance();