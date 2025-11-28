#include "victoire.h"

// Constructor
EndGameItem::EndGameItem(const sf::Vector2f& position, const sf::Vector2f& size)
{
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setPosition(position);
}

// Draw
void EndGameItem::Draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

// Collision bounds
sf::FloatRect EndGameItem::GetBounds() const
{
    return m_shape.getGlobalBounds();
}
