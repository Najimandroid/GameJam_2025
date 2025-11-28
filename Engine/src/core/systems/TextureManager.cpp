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

	sf::Texture textureJump;
	if (!textureJump.loadFromFile("assets/textures/Player/jump.png"))
	{
		std::cerr << "failed to load jump texture";
	}

	playerTextures.emplace_back(std::make_shared<sf::Texture>(textureIdle));
	playerTextures.emplace_back(std::make_shared<sf::Texture>(textureWalk));
	playerTextures.emplace_back(std::make_shared<sf::Texture>(textureJump));
}


std::vector<std::shared_ptr<sf::Texture>>& TextureManager::getPlayerTextures()
{
	return playerTextures;
}

TextureManager* TextureManager::getInstance() {
	static TextureManager instance; 
	return &instance;
}