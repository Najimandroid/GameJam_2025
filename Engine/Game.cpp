#include "Game.h"

Game::Game()
{
}

void Game::Run()
{
	sf::RenderWindow window(sf::VideoMode({ 500, 500 }), "IDF Map");

	while (window.isOpen()) {

        while (const auto event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        deltaTime = deltaClock.getElapsedTime().asSeconds();

	}
    window.clear();

    window.display();

}
