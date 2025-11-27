#include "UI_Text.h"

// Constructor with size and position, default text "Text"
UI_Text::UI_Text(sf::Vector2f position, sf::Vector2f size)
    : m_text(m_font, "Text", 30) // default character size 30
{
    // Load font from file
    auto success = m_font.openFromFile("assets/fonts/MPLUSRounded1c-Medium.ttf");

    // Configure text appearance
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

// Constructor with custom text
UI_Text::UI_Text(sf::Vector2f position, sf::Vector2f size, const std::string& text)
    : m_text(m_font, text, 30) // default character size 30
{
    // Load font from file
    auto success = m_font.openFromFile("assets/fonts/MPLUSRounded1c-Medium.ttf");

    // Configure text appearance
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

// Constructor with custom text and custom character size
UI_Text::UI_Text(sf::Vector2f position, sf::Vector2f size, const std::string& text, float characterSize)
    : m_text(m_font, text, characterSize)
{
    // Load font from file
    auto success = m_font.openFromFile("assets/fonts/MPLUSRounded1c-Medium.ttf");

    // Configure text appearance
    m_text.setPosition(position);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1.5f);
}

// Set the displayed text string
void UI_Text::set_text(const std::string& text)
{
    m_text.setString(text);
}

// Set the fill color of the text
void UI_Text::set_text_color(const sf::Color& color)
{
    m_text.setFillColor(color);

    if (color.a == 0)
        m_text.setOutlineColor(sf::Color(0, 0, 0, 0));
}

// Set the character size of the text
void UI_Text::set_character_size(unsigned int size)
{
    m_text.setCharacterSize(size);
}

// Update function called every frame
void UI_Text::update(float deltaTime)
{
    m_text.setPosition(m_position);
}

// Render the text if visible
void UI_Text::render(sf::RenderWindow& window)
{
    if (m_isVisible)
        window.draw(m_text);
}

sf::Text& UI_Text::get_text()
{
    return m_text;
}