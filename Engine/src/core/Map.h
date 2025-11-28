#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map
{
public:
    static Map* getInstance();
    bool LoadFromFile(const std::string& filePath);
    void Draw(sf::RenderWindow& window);
    void DrawDebug(sf::RenderWindow& window);
    void LoadTexture();
    sf::Vector2f GetPlayerSpawn() const;
    sf::Vector2f GetItemSpawn() const;
    std::vector<sf::FloatRect> GetCollisionBounds() const;
    std::vector<sf::FloatRect> GetSlowBounds() const;
    std::vector<sf::FloatRect> GetDeadlyBounds() const;
    void Reset();
    bool isLoaded() { return loaded; }
    void update(float dt);
private:
    static Map* instance;
    Map(){}
    void CreateTile(char symbol, float x, float y);

    std::vector<sf::Sprite> m_tiles;
    std::vector<sf::FloatRect> m_slowBounds;
    std::vector<sf::RectangleShape> m_debugColliders;
    std::vector<sf::Sprite> m_deadlyBounds;

    std::string m_filePath;

    sf::Texture m_wallTexture;
    sf::Texture m_groundTexture;
    sf::Texture m_vine1Texture;
    sf::Texture m_vine2Texture;
    sf::Texture m_platform;
    sf::Texture m_platform2;
    sf::Texture m_platform3;
    sf::Texture m_platform4;
    sf::Texture m_deadlyTexture;

    float m_tileSize;

    sf::Vector2f m_playerSpawn;
    sf::Vector2f m_itemSpawn;

    bool m_showDebug = false;
    float debugActivationTime = 2.5f;
    float debugCooldown = 0.f;

    bool loaded = false;
};

extern Map* managerMap;
