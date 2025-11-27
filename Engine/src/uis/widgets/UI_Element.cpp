#include "UI_Element.h"

UI_Element::UI_Element(sf::Vector2f position, sf::Vector2f size)
    : m_size(size), m_position(position)
{
}

void UI_Element::set_position(sf::Vector2f newPosition)
{
    m_position = newPosition;
}

void UI_Element::set_size(sf::Vector2f newSize)
{
    m_size = newSize;
}

void UI_Element::set_visible(bool isVisible)
{
    m_isVisible = isVisible;
}

sf::Vector2f UI_Element::get_position() const
{
    return m_position;
}

sf::Vector2f UI_Element::get_size() const
{
    return m_size;
}

sf::FloatRect UI_Element::get_bounds() const
{
    return sf::FloatRect{ m_position, m_size };
}

bool UI_Element::is_visible() const
{
    return m_isVisible;
}
