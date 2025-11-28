#include "Game.h"

#include <memory>

std::thread tCollisions(&HandleCollisions::collisions, managerCollisions);

Game::Game():
	m_uiManager(std::make_unique<UI_Manager>())
{
	managerMap->LoadTexture();
	m_window.create(sf::VideoMode::getDesktopMode(), "Game Jam 2025", sf::Style::None); //sf::Style::None
	m_window.setFramerateLimit(m_frameRate);
	center_window();

	ImGui::SFML::Init(m_window);
	init_cameras();
}

void Game::runGameLoop()
{
	// Temporary
	managerMap->LoadFromFile("assets/levels/Map.txt");

	TextureManager* textureManager = TextureManager::getInstance();

	sf::Texture texture;
	texture.loadFromFile("assets/textures/Player/Idle.png");

	managerEntity->createPlayer(textureManager->getPlayerTextures(), sf::Vector2f(500, 0), 400);

	m_uiManager->generate_menu();

	while (m_window.isOpen())
	{
		calculate_delta_time();

		//================================================
		// Events
		poll_events();

		//================================================
		// Updates
	
		managerEntity->getAllPlayers()[0]->update(0.016f);
		//player.update(0.016f);

		//================================================
		// Render
		m_window.clear();

		// Render game
		m_window.setView(m_stageCamera);
		managerMap->Draw(m_window);

		// Render UIs
		m_window.setView(m_uiCamera);
		m_uiManager->render_uis(m_window, m_uiCamera, m_stageCamera);
		managerEntity->getAllPlayers()[0]->draw(m_window);
		//player.draw(m_window);

		m_window.display();
	}

	ImGui::SFML::Shutdown();
}

void Game::shutDown()
{
}

void Game::poll_events()
{
	while (const auto event = m_window.pollEvent())
	{
		ImGui::SFML::ProcessEvent(m_window, *event);

		m_uiManager->handle_ui_events(*event, m_window);

		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}

		if (const auto* e_keycode = event->getIf<sf::Event::KeyPressed>())
		{
			// Close game
			if (e_keycode->code == sf::Keyboard::Key::Escape)
			{
				m_window.close(); 
				managerCollisions->isGameRunning = false;
				tCollisions.join();
			}
		}
	}
}

void Game::resize_window(sf::Vector2u newSize)
{
	m_window.setSize(newSize);
}

void Game::center_window()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2u windowSize = m_window.getSize();

	int posX = (desktop.size.x - windowSize.x) / 2;
	int posY = (desktop.size.y - windowSize.y) / 2;

	m_window.setPosition(sf::Vector2i(posX, posY));
}

float Game::get_delta_time() const
{
	return m_deltaTime;
}

const sf::Vector2u Game::get_logical_resolution() const
{
	return m_logicalResolution;
}

const int Game::get_frame_rate() const
{
	return m_frameRate;
}

void Game::init_cameras()
{
	m_uiCamera.setSize(static_cast<sf::Vector2f>(m_logicalResolution));
	m_uiCamera.setCenter(m_uiCamera.getSize() / 2.f);

	m_stageCamera.setSize(static_cast<sf::Vector2f>(m_logicalResolution));
	m_stageCamera.setCenter(m_stageCamera.getSize() / 2.f);

	m_uiCamera.setViewport(sf::FloatRect{ {0.f, 0.f}, {1.f, 1.f} });
	m_stageCamera.setViewport(sf::FloatRect{ {0.f, 0.f}, {1.f, 1.f} });

	m_stageCamera.zoom(1.f);
}

void Game::debug_ui()
{
	if (m_deltaTime <= 0) return;

	ImGui::SFML::Update(m_window, sf::seconds(m_deltaTime));
	// Nothing there I guess
}

void Game::calculate_delta_time()
{
	m_deltaTime = m_deltaClock.restart().asSeconds();
}
