#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>

class Entity
{
private:
    sf::Vector2f pos;
    sf::Sprite sprite;
public:
    Entity(sf::Texture& texture, sf::Vector2f pos_);

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    sf::Sprite& getSprite();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f newPos);
};