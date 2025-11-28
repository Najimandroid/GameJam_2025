#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class TextureManager
{
private:
	std::vector<std::shared_ptr<sf::Texture>> playerTextures;
	std::vector<std::shared_ptr<sf::Texture>> glitchedTileTextures;
	TextureManager();
	static TextureManager* instance;

public:
	static TextureManager* getInstance();

	std::vector<std::shared_ptr<sf::Texture>>& getPlayerTextures();
	std::vector<std::shared_ptr<sf::Texture>>& getGlitchedTileTextures();
};

