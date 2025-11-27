#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
public:
    Map();
    bool LoadFromFile(const std::string& filePath);
    void Draw(sf::RenderWindow& window) const;
    sf::Vector2f GetPlayerSpawn() const;
    sf::Vector2f GetItemSpawn() const;
    std::vector<sf::FloatRect> GetCollisionBounds() const;
    std::vector<sf::FloatRect> GetSlowBounds() const;
    void Reset();

private:
    void CreateTile(char symbol, float x, float y);

    std::vector<sf::Sprite> m_tiles;
    std::vector<sf::FloatRect> m_slowBounds;
    std::string m_filePath;

    sf::Texture m_wallTexture;
    sf::Texture m_groundTexture;
    sf::Texture m_vine1Texture;
    sf::Texture m_vine2Texture;
    sf::Texture m_platform;
    sf::Texture m_platform2;
    sf::Texture m_platform3;
    sf::Texture m_platform4;

    float m_tileSize;

    sf::Vector2f m_playerSpawn;
    sf::Vector2f m_itemSpawn;
};


