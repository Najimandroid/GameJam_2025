#include "Player.h"

Player::Player(sf::Texture& _texture, sf::Vector2f _pos_, float _speed) : speed(_speed), Entity(_texture, _pos_) {

}


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

sf::FloatRect Player::getHB()
{
	return sf::FloatRect();
}

float Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Player::update(float dt)
{
	handleInput();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}
