#pragma once
#include "Entity.h"
#include "../../uis/UI_Manager.h"
#include "victoire.h"


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
	UI_Manager* managerUI;

	sf::Clock teleportCooldown;
	void HandleTeleport();
	const float TELEPORT_INTERVAL = 10.0f;
	
	EndGameItem* egi;
	
public:

	bool isGrounded = false;

	bool isJumping = false;

	float gravity = 9.81f * 60;
	float jumpforce = 700.f;

public:

	Player(std::vector<std::shared_ptr<sf::Texture>>& _textures, sf::Vector2f pos_, float _speed, UI_Manager* uiManager);

	void add_end_game_item(EndGameItem* egi);

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

