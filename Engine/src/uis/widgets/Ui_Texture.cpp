#include "UI_Texture.h"
#include <iostream>

/*
 * Creates a UI_Texture with a given size, position, and texture path.
 * Loads the texture, sets up the sprite, positions it, and applies scaling to fit the desired size.
 */
UI_Texture::UI_Texture(sf::Vector2f position, sf::Vector2f size, const std::string& texturePath) :
    UI_Element(position, size),
    m_sprite(m_texture) // initialize sprite with texture
{
    // Load the texture from file
    if (!m_texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture: " << texturePath << "\n";
    }

    // Set the texture rectangle to cover the full texture
    m_sprite.setTextureRect(sf::IntRect(
        { 0, 0 },
        { static_cast<int>(m_texture.getSize().x), static_cast<int>(m_texture.getSize().y) }
    ));

    // Assign the texture to the sprite and set its initial position
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);

    // Scale sprite to match desired size while preserving aspect ratio
    apply_scale();
}

/*
 * Draws the sprite to the window if it is visible.
 */
void UI_Texture::render(sf::RenderWindow& window)
{
    if (m_isVisible)
    {
        window.draw(m_sprite);
    }
}

/*
 * Loads a new texture from a file and reapplies scaling.
 */
void UI_Texture::set_texture(const std::string& texturePath)
{
    if (!m_texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture: " << texturePath << "\n";
        return;
    }

    m_sprite.setTexture(m_texture);
    apply_scale();
}

/*
 * Updates the size of the element and rescales the sprite to fit.
 */
void UI_Texture::set_size(sf::Vector2f newSize)
{
    m_size = newSize;
    apply_scale();
}

/*
 * Returns the global bounding rectangle of the sprite (for interaction detection).
 */
sf::FloatRect UI_Texture::get_bounds() const
{
    return m_sprite.getGlobalBounds();
}

/*
 * Calculates the scaling factor for the sprite to fit within m_size while preserving aspect ratio.
 */
void UI_Texture::apply_scale()
{
    sf::Vector2u texSize = m_texture.getSize();
    if (texSize.x == 0 || texSize.y == 0) return; // prevent division by zero

    float scaleX = m_size.x / static_cast<float>(texSize.x);
    float scaleY = m_size.y / static_cast<float>(texSize.y);

    // Use the smaller factor to maintain aspect ratio
    float scale = std::min(scaleX, scaleY);
    m_sprite.setScale({ scale, scale });

    // Ensure the texture rectangle still covers the entire texture
    m_sprite.setTextureRect(sf::IntRect(
        { 0, 0 },
        { static_cast<int>(m_texture.getSize().x), static_cast<int>(m_texture.getSize().y) }
    ));
}