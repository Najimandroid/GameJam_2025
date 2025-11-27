#pragma once
#include "Player.h"

class Game
{
public:
	Game();

	void Run();

private:
	sf::Clock deltaClock;

	float deltaTime;
};

