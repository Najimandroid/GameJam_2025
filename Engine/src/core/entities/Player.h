#pragma once
#include "Entity.h"

enum class PlayerState
{
	IDLE,
	WALKING,
	JUMPING,

};

class Player : public Entity
{
private:
	float speed = 100.f;
	float animationTime;
	float scale = 5.f;

	sf::RectangleShape m_hitbox;

	sf::Vector2f velocity = { 0,0 };

	std::unordered_map<PlayerState, std::shared_ptr<sf::Texture>> textures;
	std::unordered_map<PlayerState, float> animationCooldowns;

	PlayerState state;
	void HandleAutoTeleport(float dt);
	float m_teleportTimer = 0.0f;
	const float TELEPORT_INTERVAL = 10.0f;

	
public:

	bool isGrounded = false;

	bool isJumping = false;

	float gravity = 9.81f * 60;
	float jumpforce = 700.f;

public:

	Player(std::vector<std::shared_ptr<sf::Texture>>& _textures, sf::Vector2f pos_, float _speed);

	void update(float dt);

	void draw(sf::RenderWindow& window) override;

	void animate(float dt);

	void handleInput(float dt);

	sf::FloatRect getHB();

	float getSpeed();

	void setSpeed(float newSpeed);

	PlayerState getState();

	void setState(PlayerState newState);

	bool collides(const sf::Vector2f& nexPos);
};

