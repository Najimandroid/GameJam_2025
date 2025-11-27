#pragma once
#include <vector>

#include "Entity.h"
#include "Player.h"

class EntityManager
{
private:
	static EntityManager* instance;
	EntityManager() {}

	std::vector<std::shared_ptr<Entity>> allPlayers;

	std::vector<std::shared_ptr<Entity>> allEnnemies;
	std::vector<std::shared_ptr<Entity>> allEntities;


public:
	static EntityManager* getInstance();
	~EntityManager();
	void createPlayer(sf::Vector2f _pos, sf::Texture& _textPlayer, sf::Texture& _textPlayerJumpEffect, sf::Texture& _textPlayerLandEffect, float _speed, int _hp);

	std::vector<std::shared_ptr<Entity>> getAllPlayers() const;

	std::vector<std::shared_ptr<Entity>> getAllEnnemies() const;
	std::vector<std::shared_ptr<Entity>> getAllEntities() const;
};

extern EntityManager* manager;