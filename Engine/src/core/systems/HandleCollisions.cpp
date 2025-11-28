#include "HandleCollisions.h"

HandleCollisions* HandleCollisions::getInstance()
{
	if (instance == nullptr) { instance = new HandleCollisions(); }
	return instance;
}

void HandleCollisions::collisions()
{
	collisionSides.reserve(4);

	while (managerEntity->getAllPlayers().size() == 0) {}; // Wait for player

	collisionSides.clear();

	Player* player = dynamic_cast<Player*>(managerEntity->getAllPlayers()[0].get());

	int colliding = 0;


	while (isGameRunning)
	{
		collisionSides.clear();

		for (auto wall : managerMap->GetCollisionBounds()) {
			if (sf::FloatRect({ player->getHB().position.x , player->getHB().position.y + player->getHB().size.y - 1 }, { player->getHB().size.x,1 }).findIntersection(wall))
			{
				collisionSides.push_back(1); //Collision Bottom
			}
			if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, { player->getHB().size.x, 1 }).findIntersection(wall))
			{
				collisionSides.push_back(2); //Collision Top
			}
			if (sf::FloatRect({ player->getHB().position.x, player->getHB().position.y }, { 1, player->getHB().size.y }).findIntersection(wall))
			{
				collisionSides.push_back(3); //Collision Left
			}
			if (sf::FloatRect({ player->getHB().position.x + player->getHB().size.x, player->getHB().position.y }, { 1, player->getHB().size.y }).findIntersection(wall)) 
			{
				collisionSides.push_back(4); //Collision Right
			}
		}
	}
}

HandleCollisions* HandleCollisions::instance = nullptr;
HandleCollisions* managerCollisions = HandleCollisions::getInstance();