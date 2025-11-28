#include "Player.h"
#include "../systems/HandleCollisions.h"


Player::Player(std::vector<std::shared_ptr<sf::Texture>>& _textures, sf::Vector2f _pos_, float _speed, UI_Manager* uimanager) : speed(_speed), Entity(*_textures[0], _pos_)
{	
	managerUI = uimanager;

	textures.emplace(PlayerState::IDLE, _textures[0]);
	textures.emplace(PlayerState::WALKING, _textures[1]);
	textures.emplace(PlayerState::JUMPING, _textures[2]);

	animationCooldowns.emplace(PlayerState::IDLE, 0.2f);
	animationCooldowns.emplace(PlayerState::JUMPING, 0.5f);
	animationCooldowns.emplace(PlayerState::WALKING, 0.05f);
	 
	state = PlayerState::IDLE;

	sprite.setScale({ scale, scale });
	sprite.setPosition({ 500, 500 });

	m_hitbox.setSize({ 100.f, 100.f });
	
	m_hitbox.setOrigin({ 1.f, 0.f });
	sprite.setOrigin({ 1.f, 0.f });

	/*for (auto& [state_, tex] : textures)
	{
		std::cout << tex->getSize().x << std::endl;
	}*/
}


void Player::handleInput(float dt)
{
	velocity.x = 0;

	bool canWalkRight = true;
	bool canWalkLeft = true;

	for (auto i : managerCollisions->getCollisionSides())
	{
		if (i == 3) canWalkLeft = false;
		if (i == 2) canWalkRight = false;
	}

	// Check for inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		if (canWalkLeft)
		{
			velocity.x -= speed;
			if (isGrounded)
				setState(PlayerState::WALKING);
			sprite.setScale({ -scale, scale });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (canWalkRight)
		{
			velocity.x += speed;
			if (isGrounded)
				setState(PlayerState::WALKING);
			sprite.setScale({ scale, scale });
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && isGrounded)
	{
		velocity.y = -jumpforce; // initial jump velocity
		isJumping = true;
		isGrounded = false;
		setState(PlayerState::JUMPING);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		HandleTeleport();
	}
}

sf::FloatRect Player::getHB()
{
	return m_hitbox.getGlobalBounds();
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
		sprite.setTexture(*textures[newState]);
		sprite.setTextureRect(sf::IntRect({ 0, sprite.getTextureRect().position.y },
			{ sprite.getTextureRect().size.x, sprite.getTextureRect().size.y }));
	}
}

void Player::HandleTeleport()
{
	// Increase timer
	// Check if interval reached
	if (teleportCooldown.getElapsedTime().asSeconds() >= 2.f)
	{
		teleportCooldown.restart();
		// Random side: 0 = left, 1 = right
		int side = rand() % 2;

		if (side == 0)
		{
			
			pos.x -= 500.f;  // Example left position
		}
		else
		{
			// Teleport right
			pos.x += 500.f; // Example right position
		}

		// Update hitbox and sprite positions
		m_hitbox.setPosition(pos);
		sprite.setPosition(
			{
				m_hitbox.getPosition().x + m_hitbox.getSize().x / 2.f,
				m_hitbox.getPosition().y - m_hitbox.getSize().y / 2.f
			}
		);
	}
}

void Player::update(float dt)
{
	handleInput(dt);
	animate(dt);

	// Appliquer la gravité
	velocity.y += gravity * dt;

	// Calculer tentative de nouvelle position
	sf::Vector2f newPos = pos + velocity * dt;

	// Vérifier collisions horizontales
	sf::Vector2f testPosX = { newPos.x, pos.y };
	if (collides(testPosX))
	{
		velocity.x = 0;
		testPosX.x = pos.x; // annule déplacement horizontal
	}

	// Vérifier collisions verticales
	sf::Vector2f testPosY = { testPosX.x, newPos.y };
	if (collides(testPosY))
	{
		if (velocity.y > 0) // atterrissage
		{
			isGrounded = true;
			isJumping = false;
			if (state == PlayerState::JUMPING)
				setState(PlayerState::IDLE);
		}
		else if (velocity.y < 0) // plafond
		{
			isJumping = true;
		}
		velocity.y = 0;

		testPosY.y = pos.y;
	}
	else
	{
		isGrounded = false;
	}

	// Appliquer la position finale
	pos = testPosY;
	m_hitbox.setPosition(pos);

	// Synchroniser sprite avec hitbox
	sprite.setPosition(
		{
			m_hitbox.getPosition().x + m_hitbox.getSize().x / 2.f,
			m_hitbox.getPosition().y - m_hitbox.getSize().y / 2.f,
		}
		);

	for (const auto& deadly : managerMap->GetDeadlyBounds())
	{
		// Check deadly collision using findIntersection
		if (m_hitbox.getGlobalBounds().findIntersection(deadly).has_value())
		{
			// Player dies or respawns here
			pos = managerMap->GetPlayerSpawn();
			m_hitbox.setPosition(pos);

			/*sprite.setPosition(
				{
					pos.x + m_hitbox.getSize().x / 2.f,
					pos.y - m_hitbox.getSize().y / 2.f
				});*/
			managerUI->game_over_menu();

			velocity = { 0.f, 0.f };
			isGrounded = false;

			std::cout << "Player died: deadly tile collision\n";

			return; // stop update for this frame
		}
	}
}


bool Player::collides(const sf::Vector2f& testPos)
{
	sf::FloatRect hb = m_hitbox.getGlobalBounds();
	hb.position.x = testPos.x;
	hb.position.y = testPos.y;

	for (const auto& wall : managerMap->GetCollisionBounds())
	{
		if (hb.findIntersection(wall).has_value())
			return true;
	}

	return false;
}

void Player::draw(sf::RenderWindow& window)
{
	/*for (auto& [state_, tex] : textures)
	{
		if (tex.get() == &getSprite().getTexture())
			std::cout << static_cast<int>(state_) << std::endl;
	}*/
	//window.draw(m_hitbox);
	window.draw(sprite);
}

void Player::animate(float dt)
{
	
	animationTime += dt;

	if (animationTime > animationCooldowns[state])
	{
		animationTime -= animationCooldowns[state];
		if (sprite.getTextureRect().position.x + 16 < sprite.getTexture().getSize().x)
		{
			sprite.setTextureRect(sf::IntRect({ sprite.getTextureRect().position.x + 16, sprite.getTextureRect().position.y }, { sprite.getTextureRect().size.x, sprite.getTextureRect().size.y }));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect({ 0, sprite.getTextureRect().position.y },
				{ sprite.getTextureRect().size.x, sprite.getTextureRect().size.y }));
		}
	}

	sprite.setPosition(
		{
			m_hitbox.getPosition().x + m_hitbox.getSize().x / 2.f,
			m_hitbox.getPosition().y - m_hitbox.getSize().y / 2.f,
		}
	);
}
