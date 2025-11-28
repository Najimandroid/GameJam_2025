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

   

    default:
        break;
    }
}

void Map::Draw(sf::RenderWindow& window) const
{
    for (const auto& tile : m_tiles)
        window.draw(tile);
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

void Map::Reset()
{
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