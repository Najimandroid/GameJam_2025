#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include <iostream>

class Test
{
private:
    int lol;
};

int main() 
{
    sf::RenderWindow window(sf::VideoMode({ 500, 500 }), "IDF Map");
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    float deltaTime = 0.f;

    sf::CircleShape circle(999);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) 
    {
        while (const auto event = window.pollEvent()) 
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
        }

		deltaTime = deltaClock.getElapsedTime().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();

        window.draw(circle);

        ImGui::SFML::Render(window);

        std::cout << "Lol\n";

        window.display();
    }

    ImGui::SFML::Shutdown();
}