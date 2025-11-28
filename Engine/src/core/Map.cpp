#include "Map.h"
#include <fstream>
#include <iostream>
#include "systems/TextureManager.h" // ajouté pour accéder aux frames glitched

// variables d'animation locales au fichier (Map est singleton donc safe)
namespace {
	enum class TileType { Unknown, Ground, Wall, Deadly };

	std::vector<TileType> s_tileTypes;       // types correspondant aux m_tiles
	std::vector<TileType> s_deadlyTypes;     // types correspondant aux m_deadlyBounds

	// stocke l'échelle d'origine calculée pour chaque sprite (pour restauration)
	std::vector<sf::Vector2f> s_tileOriginalScales;
	std::vector<sf::Vector2f> s_deadlyOriginalScales;

	float s_animTimer = 0.f;
	std::size_t s_animFrame = 0;
	const float s_frameDuration = 0.12f; // durée d'une frame en secondes (ajustable)

	bool s_prevShowDebug = false; // état précédent pour détecter transition
}

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
    s_tileTypes.clear();
    s_tileOriginalScales.clear();
    m_deadlyBounds.clear();
    s_deadlyTypes.clear();
    s_deadlyOriginalScales.clear();

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

        // calcule et applique l'échelle pour correspondre à m_tileSize
        sf::Vector2u texSize = m_wallTexture.getSize();
        sf::Vector2f origScale{1.f, 1.f};
        if (texSize.x > 0 && texSize.y > 0)
        {
            origScale.x = m_tileSize / static_cast<float>(texSize.x);
            origScale.y = m_tileSize / static_cast<float>(texSize.y);
            tile.setScale(origScale);
        }

        m_tiles.push_back(tile);
        s_tileTypes.push_back(TileType::Wall);
        s_tileOriginalScales.push_back(origScale);
        break;
    }

    case '.': // Ground
    {
        sf::Sprite tile(m_groundTexture);
        tile.setPosition(sf::Vector2f(x, y));

        sf::Vector2u texSize = m_groundTexture.getSize();
        sf::Vector2f origScale{1.f, 1.f};
        if (texSize.x > 0 && texSize.y > 0)
        {
            origScale.x = m_tileSize / static_cast<float>(texSize.x);
            origScale.y = m_tileSize / static_cast<float>(texSize.y);
            tile.setScale(origScale);
        }

        m_tiles.push_back(tile);
        s_tileTypes.push_back(TileType::Ground);
        s_tileOriginalScales.push_back(origScale);
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

        sf::Vector2u texSize = m_deadlyTexture.getSize();
        sf::Vector2f origScale{1.f, 1.f};
        if (texSize.x > 0 && texSize.y > 0)
        {
            origScale.x = m_tileSize / static_cast<float>(texSize.x);
            origScale.y = m_tileSize / static_cast<float>(texSize.y);
            tile.setScale(origScale);
        }

        m_deadlyBounds.push_back(tile);
        s_deadlyTypes.push_back(TileType::Deadly);
        s_deadlyOriginalScales.push_back(origScale);
        break;
    }

    default:
        break;
    }
}

void Map::update(float dt)
{
    // déplacement normal
    for (auto& tile : m_tiles)
        tile.setPosition(tile.getPosition() - sf::Vector2f{ 30.f * dt, 0.f });
    for (auto& tile : m_deadlyBounds)
        tile.setPosition(tile.getPosition() - sf::Vector2f{ 30.f * dt, 0.f });

    // debug activation cooldown
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

    // Récupère frames glitched (peut être vide)
    auto& glitched = TextureManager::getInstance()->getGlitchedTileTextures();

    // Diagnostic : signale si aucune frame glitched n'est chargée
    if (glitched.empty())
    {
        static bool warned = false;
        if (!warned)
        {
            std::cerr << "Map::update - aucune texture glitched trouvée (glitched.size() == 0)\n";
            warned = true;
        }
    }

    // Détection de transition ON/OFF pour appliquer/restaurer immédiatement
    if (m_showDebug != s_prevShowDebug)
    {
        if (m_showDebug)
        {
            // ON : réinitialise l'animation et applique la première frame si disponible
            s_animTimer = 0.f;
            s_animFrame = 0;
            if (!glitched.empty() && glitched[0])
            {
                std::cerr << "Map::update - activation glitch, frames disponibles = " << glitched.size() << "\n";

                // applique la première frame tout en scalant chaque sprite pour garder la bonne taille
                sf::Vector2u gSize = glitched[0]->getSize();
                for (std::size_t i = 0; i < m_tiles.size(); ++i)
                {
                    m_tiles[i].setTexture(*glitched[0], true);
                    if (gSize.x > 0 && gSize.y > 0)
                    {
                        sf::Vector2f scale{ m_tileSize / static_cast<float>(gSize.x), m_tileSize / static_cast<float>(gSize.y) };
                        m_tiles[i].setScale(scale);
                    }
                }
                for (std::size_t i = 0; i < m_deadlyBounds.size(); ++i)
                {
                    m_deadlyBounds[i].setTexture(*glitched[0], true);
                    if (gSize.x > 0 && gSize.y > 0)
                    {
                        sf::Vector2f scale{ m_tileSize / static_cast<float>(gSize.x), m_tileSize / static_cast<float>(gSize.y) };
                        m_deadlyBounds[i].setScale(scale);
                    }
                }
            }
        }
        else
        {
            // OFF : restaure immédiatement les textures d'origine et reset animation
            std::cerr << "Map::update - désactivation glitch, restauration textures originales\n";
            for (std::size_t i = 0; i < m_tiles.size() && i < s_tileTypes.size(); ++i)
            {
                switch (s_tileTypes[i])
                {
                case TileType::Ground:
                    m_tiles[i].setTexture(m_groundTexture, true);
                    break;
                case TileType::Wall:
                    m_tiles[i].setTexture(m_wallTexture, true);
                    break;
                default:
                    break;
                }

                // restaure l'échelle d'origine si disponible
                if (i < s_tileOriginalScales.size())
                    m_tiles[i].setScale(s_tileOriginalScales[i]);
            }

            for (std::size_t i = 0; i < m_deadlyBounds.size() && i < s_deadlyTypes.size(); ++i)
            {
                switch (s_deadlyTypes[i])
                {
                case TileType::Deadly:
                    m_deadlyBounds[i].setTexture(m_deadlyTexture, true);
                    break;
                default:
                    break;
                }

                if (i < s_deadlyOriginalScales.size())
                    m_deadlyBounds[i].setScale(s_deadlyOriginalScales[i]);
            }

            s_animTimer = 0.f;
            s_animFrame = 0;
        }

        s_prevShowDebug = m_showDebug;
    }

    // Animation : n'avance la frame que si on est en debug et qu'il y a des frames
    if (m_showDebug && !glitched.empty())
    {
        s_animTimer += dt;
        if (s_animTimer >= s_frameDuration)
        {
            s_animTimer -= s_frameDuration;
            s_animFrame = (s_animFrame + 1) % glitched.size();

            // appliquer la nouvelle frame à toutes les tuiles, avec scale adapté
            if (glitched[s_animFrame])
            {
                sf::Vector2u gSize = glitched[s_animFrame]->getSize();
                for (std::size_t i = 0; i < m_tiles.size(); ++i)
                {
                    m_tiles[i].setTexture(*glitched[s_animFrame], true);
                    if (gSize.x > 0 && gSize.y > 0)
                    {
                        sf::Vector2f scale{ m_tileSize / static_cast<float>(gSize.x), m_tileSize / static_cast<float>(gSize.y) };
                        m_tiles[i].setScale(scale);
                    }
                }
                for (std::size_t i = 0; i < m_deadlyBounds.size(); ++i)
                {
                    m_deadlyBounds[i].setTexture(*glitched[s_animFrame], true);
                    if (gSize.x > 0 && gSize.y > 0)
                    {
                        sf::Vector2f scale{ m_tileSize / static_cast<float>(gSize.x), m_tileSize / static_cast<float>(gSize.y) };
                        m_deadlyBounds[i].setScale(scale);
                    }
                }
            }
        }
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