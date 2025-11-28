#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../uis/UI_Manager.h"  
#include "Map.h"  
#include "../Player.h"

/*
 * Game class
 * -----------
 * Game class manages the main game loop and all core systems.
 * Responsibilities include:
 *   - Creating and managing the SFML window
 *   - Handling input and events
 *   - Managing the stage and UI systems
 *   - Updating and rendering game objects each frame
 */
class Game
{
public:
    // Constructor initializes the window, cameras, and game systems
    Game();

    // Starts the main game loop, updates game state, and renders each frame
    void runGameLoop();

    // Shuts down the game and cleans up resources
    void shutDown();

    // Polls and processes all window events
    void poll_events();

    // Handles window resizing
    void resize_window(sf::Vector2u newSize);

    // Centers the game window on the user's desktop
    void center_window();

    // Get delta time
    float get_delta_time() const;

    const sf::Vector2u get_logical_resolution() const;

    const int get_frame_rate() const;

private:
    // Initializes UI and stage cameras with correct viewports and zoom
    void init_cameras();

    // Renders debug UI when DEBUG_MODE is enabled
    void debug_ui();

    // Calculates delta time and applies pause/speed modifiers
    void calculate_delta_time();

private:

    // Window and Cameras (Views)
    sf::RenderWindow m_window;
    sf::View m_uiCamera;           // Camera used to render UI elements
    sf::View m_stageCamera;        // Camera used to render the gameplay/stage

    sf::Clock m_deltaClock;        // Clock to compute deltaTime between frames
    float m_deltaTime = 0.0f;      // Delta time in seconds since the last frame

    const int m_frameRate = 60;    // Maximum framerate
    const sf::Vector2u m_logicalResolution = { 1920, 1080 }; // Reference resolution

    // Mouse and Inputs
    bool m_isDragging = false;     // Indicates if the user is dragging the camera
    sf::Vector2i m_lastMousePos{ 0, 0 };

    // We'll add unique_ptrs of all our other systems
    std::unique_ptr<UI_Manager> m_uiManager;
    std::unique_ptr<Map> m_map;
};