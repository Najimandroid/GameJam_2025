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

void UI_Manager::init(Map* map)
{
    m_map = map;
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

void UI_Manager::generate_menu()
{
    m_uiElements.clear();

    auto assetBackground = std::make_shared<UI_Texture>(
        sf::Vector2f{ 0 , 0 },
        sf::Vector2f{ 1920 , 1080 },
        "assets/textures/Background.png"
    );

    auto title = std::make_shared<UI_Texture>(
        sf::Vector2f{ 100.f, 100.f },
        sf::Vector2f{ 860.f, 330.f },
        "assets/textures/title.png"
    );

    auto play = std::make_shared<UI_TextButton>(
        sf::Vector2f{ 200.f , 480.f },
        sf::Vector2f{ 400 , 200 },
        ""
    );
    play->set_fill_color(sf::Color::Transparent);
    play->set_callback(
        [this]()
        {
            m_pendingAction = [this]()
                {
                    m_map->Reset();
                    m_launchGameCallback();
                    m_uiElements.clear();
                };
        }
    );

    auto assetPlay = std::make_shared<UI_Texture>(
        sf::Vector2f{ 200.f , 480.f },
        sf::Vector2f{ 400 , 200 },
        "assets/textures/start.png"
    );

    auto exit = std::make_shared<UI_TextButton>(
        sf::Vector2f{ 600.f , 480.f },
        sf::Vector2f{ 400 , 200 },
        ""
    );
    exit->set_fill_color(sf::Color::Transparent);
    auto assetExit = std::make_shared<UI_Texture>(
        sf::Vector2f{ 600.f , 480.f },
        sf::Vector2f{ 400 , 200 },
        "assets/textures/quit.png"
    );

    add_ui_element(assetBackground);

    add_ui_element(title);
    add_ui_element(assetPlay);
    add_ui_element(play);
    add_ui_element(assetExit);
    add_ui_element(exit);
    
}
void UI_Manager::win_menu()
{
    m_uiElements.clear();

    auto background = std::make_shared<UI_Texture>(
        sf::Vector2f{ 0 , 0 },
        sf::Vector2f{ 1920 , 1080 },
        "assets/textures/Background.png"
    );

    auto winTitle = std::make_shared<UI_Text>(
        sf::Vector2f{ 650.f, 100.f },
        sf::Vector2f{ 1000.f, 1000.f },
        "  You Win ! ",
        70
    );

    auto exit = std::make_shared<UI_TextButton>(
        sf::Vector2f{ 1100.f, 500.f },
        sf::Vector2f{ 200.f, 190.f },

        "   "
    );

    exit->set_fill_color(sf::Color::Transparent);
    auto assetExit = std::make_shared<UI_Texture>(
        sf::Vector2f{ 1100 , 500 },
        sf::Vector2f{ 306 , 187 },
        "assets/textures/quit.png"
    );

    exit->set_callback([this]
    {

    });

    add_ui_element(background);
    add_ui_element(winTitle);
    add_ui_element(exit);
}

void UI_Manager::game_over_menu()
{
    m_uiElements.clear();

    auto background = std::make_shared<UI_Texture>(
        sf::Vector2f{ 0 , 0 },
        sf::Vector2f{ 1920 , 1080 },
        "assets/textures/Background.png"
    );

    auto winTitle = std::make_shared<UI_Text>(
        sf::Vector2f{ 650.f, 100.f },
        sf::Vector2f{ 1000.f, 1000.f },
        "  GAME OVER ",
        70
    );

    auto exit = std::make_shared<UI_TextButton>(
        sf::Vector2f{ 1100.f, 500.f },
        sf::Vector2f{ 200.f, 190.f },

        "   "
    );
    exit->set_callback([this]()
        {
            m_pendingAction = [this]()
                {
                    generate_menu();
                };
        }
    );
        
    exit->set_fill_color(sf::Color::Transparent);
    auto assetExit = std::make_shared<UI_Texture>(
        sf::Vector2f{ 1100 , 500 },
        sf::Vector2f{ 306 , 187 },
        "assets/textures/quit.png"
    );

    /*exit->set_callback([this]
    {
        
    });*/

    add_ui_element(background);
    add_ui_element(winTitle);
    add_ui_element(assetExit);
    add_ui_element(exit);
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

void UI_Manager::set_game_launch_callback(std::function<void()> callback)
{
    m_launchGameCallback = callback;
}
