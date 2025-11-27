#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	float speed;

	sf::Vector2f velocity = { 0,0 };

public:
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void handleInput();
	sf::FloatRect getHB();
	float getSpeed();
	void setSpeed(float newSpeed);
};

