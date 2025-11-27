#include "UI_Manager.h"

#include "../core/Game.h"

// Widgets
#include "widgets/UI_Text.h"
#include "widgets/UI_TextButton.h"
#include "widgets/UI_Texture.h"

#include <iostream>

UI_Manager::UI_Manager()
{
    m_uiElements.reserve(5);
}

// Add a UI element to the manager
void UI_Manager::add_ui_element(std::shared_ptr<UI_Element> element)
{
    m_uiElements.push_back(element);
}

// Update all UI elements (called each frame)
void UI_Manager::update_uis(float deltaTime)
{
    for (auto& element : m_uiElements)
    {
        element->update(deltaTime);
    }
}

// Render all UI elements
// Handles world-space vs screen-space rendering by switching the view as needed
void UI_Manager::render_uis(sf::RenderWindow& window, sf::View& uiView, sf::View& worldView)
{
    for (auto& element : m_uiElements)
    {
        if (element->isWorldSpaceUi)
        {
            window.setView(worldView);
            element->render(window);
            window.setView(uiView);
        }
        else
        {
            element->render(window);
        }
    }
}

// Handle input events for all UI elements
// Executes deferred actions after processing events
void UI_Manager::handle_ui_events(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& uiElement : m_uiElements)
    {
        uiElement->handle_event(event, window);
    }

    // Execute deferred action if set by button callbacks
    if (m_pendingAction)
    {
        auto action = m_pendingAction;
        m_pendingAction = nullptr;
        action();
    }
}

void UI_Manager::generate_test_menu()
{
    m_uiElements.clear();

    auto title = std::make_shared<UI_Text>(
        sf::Vector2f{ 50.f, 50.f },
        sf::Vector2f{ 0.f, 0.f },
        "Test Text",
        48
    );

    auto button = std::make_shared<UI_TextButton>(
        sf::Vector2f{ 100.f, 300.f },
        sf::Vector2f{ 200.f, 80.f },
        "Test Button"
    );
    button->set_callback([this]()
        {
            m_pendingAction = [this]() {
                std::cout << "Button clicked!\n";
                };
        });

    auto texture = std::make_shared<UI_Texture>(
        sf::Vector2f{ 0.f, 0.f },
        sf::Vector2f{ 1920.f, 1080.f },
        "assets/textures/cat.png"
    );

    add_ui_element(texture);
    add_ui_element(button);      
    add_ui_element(title);
}

bool UI_Manager::is_mouse_over_ui(const sf::Vector2i& worldPosition) const
{
    for (auto& e : m_uiElements)
    {
        if (!e) continue;
        sf::FloatRect b = e->get_bounds();
        if (b.contains(static_cast<sf::Vector2f>(worldPosition))) return true;
    }
    return false;
}