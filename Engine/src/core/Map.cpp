#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map() : m_tileSize(120.0f)
{
    if (!m_groundTexture.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load ground texture\n";
    }

    if (!m_wallTexture.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load wall texture\n";
    }

    if (!m_vine1Texture.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load vine1 texture\n";
    }

    if (!m_vine2Texture.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load vine2 texture\n";
    }

    if (!m_platform.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load Platform texture\n";
    }

    if (!m_platform2.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load Platform2 texture\n";
    }

    if (!m_platform3.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load Platform3 texture\n";
    }

    if (!m_platform4.loadFromFile("assets/textures/placeholder_tile_ground.png"))
    {
        std::cerr << "Error: Failed to load Platform4 texture\n";
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

    case '*':
    {
        sf::Sprite tile(m_vine1Texture);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);

        m_slowBounds.push_back(sf::FloatRect({ x, y }, { m_tileSize, m_tileSize }));
        break;
    }

    case '+':
    {
        sf::Sprite tile(m_vine2Texture);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);

        m_slowBounds.push_back(sf::FloatRect({ x, y }, { m_tileSize, m_tileSize }));
        break;
    }

    case '1': // platform
    {
        sf::Sprite tile(m_platform);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);
        break;
    }

    case '2': // platform2
    {
        sf::Sprite tile(m_platform2);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);
        break;
    }

    case '4': // platform4
    {
        sf::Sprite tile(m_platform4);
        tile.setPosition(sf::Vector2f(x, y));
        m_tiles.push_back(tile);
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



