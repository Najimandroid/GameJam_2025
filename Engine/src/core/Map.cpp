#include "Map.h"
#include <fstream>
#include <iostream>

Map* Map::getInstance()
{
    if (instance == nullptr) { instance = new Map(); }
    return instance;
}

void Map::LoadTexture()
{
    m_tileSize = 120.0f;
    if (!m_groundTexture.loadFromFile("assets/textures/sol.png"))
    {
        std::cerr << "Error: Failed to load ground texture\n";
    }

    if (!m_wallTexture.loadFromFile("assets/textures/wall.png"))
    {
        std::cerr << "Error: Failed to load wall texture\n";
    }  
    if (!m_deadlyTexture.loadFromFile("assets/textures/kill.png"))
    {
        std::cerr << "Error: Failed to load deadly texture\n";
    }
}

bool Map::LoadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open map file: " << filePath << std::endl;
        return false;
    }

    m_tiles.clear();
    m_slowBounds.clear();

    std::string line;
    int row = 0;
    while (std::getline(file, line))
    {
        for (int col = 0; col < static_cast<int>(line.size()); ++col)
        {
            char symbol = line[col];
            CreateTile(symbol, col * m_tileSize, row * m_tileSize);
        }
        ++row;
    }

    file.close();

    for (const auto& b : GetCollisionBounds())
    {
        sf::RectangleShape rect(b.size);
        rect.setPosition(b.position);

        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(2.f);
        rect.setOutlineColor(sf::Color::Blue);

        m_debugColliders.push_back(rect);
    }

    for (const auto& db : GetDeadlyBounds())
    {
        sf::RectangleShape rect(db.size);
        rect.setPosition(db.position);

        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(2.f);
        rect.setOutlineColor(sf::Color::Red);

        m_debugColliders.push_back(rect);
    }

    loaded = true;

    return true;
}

void Map::CreateTile(char symbol, float x, float y)
{
    switch (symbol)
    {
    case '#': //wall
    {
        sf::Sprite tile(m_wallTexture);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);
        break;
    }

    case '.': // Ground
    {
        sf::Sprite tile(m_groundTexture);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);
        break;
    }

    case 'P':
    {
        m_playerSpawn = { x, y };
        break;
    }

    case 'C':
    {
        m_itemSpawn = { x, y };
        break;
    }
    case 'X': // Deadly wall
    {
        sf::Sprite tile(m_deadlyTexture);
        tile.setPosition(sf::Vector2f(x, y));
        m_deadlyBounds.push_back(tile);
        break;
    }

   

    default:
        break;
    }
}

void Map::update(float dt)
{
    for (auto& tile : m_tiles)
        tile.setPosition(tile.getPosition() - sf::Vector2f{ 30.f * dt, 0.f });
    for (auto& tile : m_deadlyBounds)
        tile.setPosition(tile.getPosition() - sf::Vector2f{ 30.f * dt, 0.f });

    if (m_showDebug)
    {
        debugCooldown += dt;

        if (debugCooldown >= debugActivationTime)
        {
            m_showDebug = false;
            debugCooldown = 0.f;
        }
    }

    for (auto& dc : m_debugColliders)
    {
        dc.setPosition(dc.getPosition() - sf::Vector2f{ 30.f * dt, 0.f });
    }
}

void Map::Draw(sf::RenderWindow& window)
{
    for (const auto& tile : m_tiles)
        window.draw(tile);

    for (const auto& dead : m_deadlyBounds)
        window.draw(dead);
}

void Map::DrawDebug(sf::RenderWindow& window)
{
    int randomNum = rand() % 75 + 1;

    if (randomNum == 5 && debugCooldown == 0.f)
    {
        m_showDebug = true;
    }

    if (m_showDebug)
    {
        for (const auto& rect : m_debugColliders)
            window.draw(rect);
    }
}

sf::Vector2f Map::GetPlayerSpawn() const
{
    return m_playerSpawn;
}

sf::Vector2f Map::GetItemSpawn() const
{
    return m_itemSpawn;
}

std::vector<sf::FloatRect> Map::GetCollisionBounds() const {
    std::vector<sf::FloatRect> bounds;
    for (const auto& tile : m_tiles) {
        bounds.push_back(tile.getGlobalBounds());
    }
    return bounds;
}

std::vector<sf::FloatRect> Map::GetSlowBounds() const
{
    return m_slowBounds;
}

std::vector<sf::FloatRect> Map::GetDeadlyBounds() const
{
    std::vector<sf::FloatRect> deadlyBoundsRects;

    for (auto& db : m_deadlyBounds)
    {
        deadlyBoundsRects.push_back(db.getGlobalBounds());
    }

    return deadlyBoundsRects;
}


void Map::Reset()
{
    loaded = false;
    if (!m_filePath.empty())
    {
        LoadFromFile(m_filePath);
    }
    else
    {
        std::cerr << "Warning: Map::Reset called but no file path is stored.\n";
    }
}

Map* Map::instance = nullptr;
Map* managerMap = Map::getInstance();