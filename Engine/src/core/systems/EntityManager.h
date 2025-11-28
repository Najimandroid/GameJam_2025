#pragma once
#include <vector>

#include "../entities/Entity.h"
#include "../entities/Player.h"

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
	std::shared_ptr<Player> createPlayer(std::vector<std::shared_ptr<sf::Texture>>& _textPlayer, sf::Vector2f _pos, float _speed, UI_Manager* uimanager);

	std::vector<std::shared_ptr<Entity>> getAllPlayers() const;

	std::vector<std::shared_ptr<Entity>> getAllEnnemies() const;
	std::vector<std::shared_ptr<Entity>> getAllEntities() const;
};

extern EntityManager* managerEntity;