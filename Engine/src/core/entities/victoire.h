#pragma once
#include <SFML/Graphics.hpp>

class EndGameItem
{
public:
    EndGameItem(const sf::Vector2f& position, const sf::Vector2f& size);

    // Public functions
    void Draw(sf::RenderWindow& window);
    sf::FloatRect GetBounds() const;


private:
    // Private members
    sf::RectangleShape m_shape;
};
