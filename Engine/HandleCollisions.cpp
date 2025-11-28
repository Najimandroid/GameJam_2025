#include "HandleCollisions.h"


HandleCollisions* HandleCollisions::getInstance()
{
	if (instance == nullptr) { instance = new HandleCollisions(); }
	return instance;
}




void HandleCollisions::collisions()
{
	while (managerEntity->getAllPlayers().size() == 0) {}

	Player* player = dynamic_cast<Player*>(managerEntity->getAllPlayers()[0].get());

	while (isGameRunning)
	{
		for (auto wall : managerMap->GetCollisionBounds()) {
			if (sf::FloatRect({ player->getHB().position.x , player->getHB().position.y + player->getHB().size.y - 1 }, { player->getHB().size.x,1 }).findIntersection(wall))
			{
				managerCollisions->collisionSide = 1; //Collision Bottom
			}
			if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, { player->getHB().size.x, 1 }).findIntersection(wall))
			{
				managerCollisions->collisionSide = 2; //Collision Top
			}
			if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, { 1, player->getHB().size.y }).findIntersection(wall))
			{
				managerCollisions->collisionSide = 3; //Collision Left
			}
			if (sf::FloatRect({ player->getHB().position.x + player->getHB().size.x, player->getHB().position.y }, { 1, player->getHB().size.y }).findIntersection(wall)) {
				managerCollisions->collisionSide = 4; //Collision Right
			}
		}
		managerCollisions->collisionSide = 0;
	}
}

HandleCollisions* HandleCollisions::instance = nullptr;
HandleCollisions* managerCollisions = HandleCollisions::getInstance();