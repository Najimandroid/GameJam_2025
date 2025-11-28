#pragma once

#include "widgets/UI_Element.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>

/*
 * UI_Manager class
 * ----------------
 * UIManager handles all User Interface (UI) elements in the game.
 * Responsibilities include:
 *   - Initializing UI elements with references to game data and stage
 *   - Updating and rendering all UI elements
 *   - Handling input events (mouse clicks, drags, etc.)
 *   - Generating different UI screens (Fish Tank, Upgrades, Equip, Battle)
 *
 * UI elements can be either:
 *   - Screen-space or
 *   - World-space (attached to the game world, e.g.)
*/
class UI_Manager
{
public:

    UI_Manager();

    // Add a single UI element to the manager
    void add_ui_element(std::shared_ptr<UI_Element> element);

    // Update all UI elements
    void update_uis(float deltaTime);

    // Render all UI elements, handling screen-space vs world-space rendering
    void render_uis(sf::RenderWindow& window, sf::View& uiView, sf::View& worldView);

    // Handle input events for all UI elements
    void handle_ui_events(const sf::Event& event, const sf::RenderWindow& window);

    // Generate specific UI layouts/screens
    // void generate_X_menu();
    void generate_menu();

    void win_menu();

    void game_over_menu();

    // Returns true if a given world position overlaps any UI element
    bool is_mouse_over_ui(const sf::Vector2i& worldPosition) const;

private:

    std::vector<std::shared_ptr<UI_Element>> m_uiElements;      // All active UI elements

    std::function<void()> m_pendingAction;                      // Deferred action triggered by UI
};