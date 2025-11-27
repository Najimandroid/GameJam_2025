#pragma once

#include "UI_Element.h"

#include <functional>
#include <optional>

/*
 * UI_TextButton represents a clickable button in the UI.
 * Inherits from UIElement and adds:
 *  - Rectangle shape
 *  - Text label
 *  - Callback function for click events
 */
class UI_TextButton : public UI_Element
{
public:

    // Constructors
    UI_TextButton(sf::Vector2f position, sf::Vector2f size);
    UI_TextButton(sf::Vector2f position, sf::Vector2f size, const std::string& text);

    // Set the function to call when the button is clicked
    void set_callback(std::function<void()> callback);

    // Centers the text inside the button rectangle
    void center_text();

    // Text setters
    void set_text(const std::string& text);
    void set_text_size(unsigned int size);
    void set_text_color(const sf::Color& color);

    // Shape appearance setters
    void set_fill_color(const sf::Color& color);
    void set_outline(float thickness, const sf::Color& color);

    // Override UIElement functions
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void handle_event(const sf::Event& event, const sf::RenderWindow& window) override;
    sf::FloatRect get_bounds() const override;

protected:

    sf::RectangleShape m_shape;         // Button background rectangle
    sf::Text m_text;                    // Button label text
    sf::Font m_font;                    // Font used for the text
    std::function<void()> m_callback;   // Function to execute on click
};