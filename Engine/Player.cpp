#include "Player.h"

Player::Player(std::vector<std::shared_ptr<sf::Texture>>& _textures, sf::Vector2f _pos_, float _speed) : speed(_speed), Entity(*_textures[0], _pos_)
{
	textures.emplace(PlayerState::Idle, _textures[0]);
	textures.emplace(PlayerState::Walk, _textures[1]);

	animationCooldowns.emplace(PlayerState::Idle, 0.2f);
	animationCooldowns.emplace(PlayerState::Walk, 0.05f);

	state = PlayerState::Idle;

	getSprite().setScale({ scale, scale });
	getSprite().setPosition({ 500, 500 });
}


void Player::handleInput()
{
	velocity = { 0,0 };

	// Check for inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		velocity.x -= 1.f;
		setState(PlayerState::Walk);
		getSprite().setScale({ -scale, scale });

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x += 1.f;
		setState(PlayerState::Walk);
		getSprite().setScale({ scale, scale });


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		velocity.y -= 1.f;
		setState(PlayerState::Idle);
		getSprite().setScale({ scale, scale });


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		velocity.y += 1.f;
		setState(PlayerState::Idle);
		getSprite().setScale({ scale, scale });
	}
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

PlayerState Player::getState()
{
	return state;
}

void Player::setState(PlayerState newState)
{
	if (newState != state)
	{
		state = newState;
		getSprite().setTexture(*textures[newState]);
		getSprite().setTextureRect(sf::IntRect({ 0, getSprite().getTextureRect().position.y },
			{ getSprite().getTextureRect().size.x, getSprite().getTextureRect().size.y }));
	}
}

void Player::update(float dt)
{
	handleInput();
	animationTime += dt;
	if (animationTime > animationCooldowns[state])
	{
		animationTime -= animationCooldowns[state];
		if (getSprite().getTextureRect().position.x + 16 < getSprite().getTexture().getSize().x)
		{
			getSprite().setTextureRect(sf::IntRect({ getSprite().getTextureRect().position.x + 16, getSprite().getTextureRect().position.y}, { getSprite().getTextureRect().size.x, getSprite().getTextureRect().size.y }));
		}
		else
		{
			getSprite().setTextureRect(sf::IntRect({ 0, getSprite().getTextureRect().position.y}, 
				{ getSprite().getTextureRect().size.x, getSprite().getTextureRect().size.y }));
		}
	}

	getSprite().move(velocity * dt * speed);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}
