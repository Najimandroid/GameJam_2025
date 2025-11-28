#include "TextureManager.h"
#include <memory>
#include <string>

TextureManager* TextureManager::instance = nullptr;

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

	// Exemple : charge un set de frames "glitch_0.png" .. "glitch_5.png"
	const int maxFrames = 6;
	for (int i = 0; i < maxFrames; ++i)
	{
		auto tex = std::make_shared<sf::Texture>();
		std::string path = "assets/textures/Glitch/tile" + std::to_string(i) + ".png";
		if (!tex->loadFromFile(path))
		{
			std::cerr << "TextureManager: failed to load " << path << std::endl;
			// Ne push pas le pointeur si échec
			continue;
		}
		glitchedTileTextures.push_back(tex);
	}

	std::cerr << "TextureManager: loaded " << glitchedTileTextures.size() << " glitched tile frames\n";
}

TextureManager* TextureManager::getInstance()
{
	if (instance == nullptr)
		instance = new TextureManager();
	return instance;
}

std::vector<std::shared_ptr<sf::Texture>>& TextureManager::getPlayerTextures()
{
	return playerTextures;
}

std::vector<std::shared_ptr<sf::Texture>>& TextureManager::getGlitchedTileTextures()
{
	return glitchedTileTextures;
}