#include "TextureManager.h"

TextureManager::TextureManager()
{
	sf::Texture textureIdle;
	if (!textureIdle.loadFromFile("assets/textures/Player/idle.png"))
	{
		std::cerr << "failed to load idle texture";
	}

	sf::Texture textureWalk;
	if (!textureWalk.loadFromFile("assets/textures/Player/walk.png"))
	{
		std::cerr << "failed to load walk texture";
	}

	playerTextures.push_back(std::make_shared<sf::Texture>(textureIdle));
	playerTextures.push_back(std::make_shared<sf::Texture>(textureWalk));
}


std::vector<std::shared_ptr<sf::Texture>>& TextureManager::getPlayerTextures()
{
	return playerTextures;
}

TextureManager* TextureManager::getInstance() {
	static TextureManager instance; 
	return &instance;
}