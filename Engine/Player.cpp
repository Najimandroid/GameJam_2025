#include "Player.h"



void Player::handleInput()
{
	velocity = { 0,0 };

	// Check for inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		velocity.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		velocity.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		velocity.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		velocity.y += 1.f;
}
