#include "EntityManager.h"


EntityManager* EntityManager::getInstance()
{
	if (instance == nullptr) { instance = new EntityManager(); }
	return instance;
}

EntityManager::~EntityManager()
{
	allPlayers.clear();

	allEnnemies.clear();
	allEntities.clear();
}
void EntityManager::createPlayer(sf::Vector2f _pos, sf::Texture& _textPlayer, sf::Texture& _textPlayerJumpEffect, sf::Texture& _textPlayerLandEffect, float _speed, int _hp)
{
	std::shared_ptr<Player> p = std::make_shared<Player>(_pos, _textPlayer, _textPlayerJumpEffect, _textPlayerLandEffect, _speed, _hp);
	allPlayers.push_back(p);
	allEntities.push_back(p);
}

std::vector<std::shared_ptr<Entity>> EntityManager::getAllPlayers() const { return allPlayers; }

std::vector<std::shared_ptr<Entity>> EntityManager::getAllEnnemies() const { return allEnnemies; }
std::vector<std::shared_ptr<Entity>> EntityManager::getAllEntities() const { return allEntities; }

EntityManager* EntityManager::instance = nullptr;
EntityManager* manager = EntityManager::getInstance();