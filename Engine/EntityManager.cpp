#include "EntityManager.h"
#include "TextureManager.h"


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
void EntityManager::createPlayer(std::vector<std::shared_ptr<sf::Texture>>& _textPlayer, sf::Vector2f _pos, float _speed)
{
	std::shared_ptr<Player> p = std::make_shared<Player>(_textPlayer, _pos, _speed);
	allPlayers.push_back(p);
	allEntities.push_back(p);
}

std::vector<std::shared_ptr<Entity>> EntityManager::getAllPlayers() const { return allPlayers; }

std::vector<std::shared_ptr<Entity>> EntityManager::getAllEnnemies() const { return allEnnemies; }
std::vector<std::shared_ptr<Entity>> EntityManager::getAllEntities() const { return allEntities; }

EntityManager* EntityManager::instance = nullptr;
EntityManager* managerEntity = EntityManager::getInstance();