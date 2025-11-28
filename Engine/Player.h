#pragma once
#include "Entity.h"

enum class PlayerState
{
	Idle,
	Walk,
	Jump,

};

class Player : public Entity
{
private:
	float speed;
	float animationTime;
	float scale = 5.f;

	sf::Vector2f velocity = { 0,0 };

	std::unordered_map<PlayerState, std::shared_ptr<sf::Texture>> textures;
	std::unordered_map<PlayerState, float> animationCooldowns;

	PlayerState state;

public:

	Player(sf::Texture& texture, sf::Vector2f pos_, float _speed);

	void update(float dt);

	void draw(sf::RenderWindow& window) override;

	void handleInput();

	sf::FloatRect getHB();

	float getSpeed();

	void setSpeed(float newSpeed);

	PlayerState getState();

	void setState(PlayerState newState);
};

