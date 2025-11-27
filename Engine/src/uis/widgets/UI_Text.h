#pragma once

#include "UI_Element.h"

/*
 * UI_Text
 * -------------
 * A UI element that displays text on the screen.
 * Supports changing text, color, and character size.
 * Can be positioned in screen-space or world-space.
 */
class UI_Text : public UI_Element
{
public:

    // Constructor: default text "Text" and character size 30
    UI_Text(sf::Vector2f position, sf::Vector2f size);

    // Constructor: custom text with default character size 30
    UI_Text(sf::Vector2f position, sf::Vector2f size, const std::string& text);

    // Constructor: custom text with custom character size
    UI_Text(sf::Vector2f position, sf::Vector2f size, const std::string& text, float characterSize);

    // Set the displayed text string
    void set_text(const std::string& text);

    // Set the text fill color
    void set_text_color(const sf::Color& color);

    // Set the character size of the text
    void set_character_size(unsigned int size);

    // Called every frame to update the element
    void update(float deltaTime) override;

    // Draw the text to the given window
    void render(sf::RenderWindow& window) override;

    // Getter
    sf::Text& get_text();

protected:

    sf::Text m_text;
    sf::Font m_font;
};