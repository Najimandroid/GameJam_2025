#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
private:
    sf::Vector2f pos;
    sf::Sprite sprite;
public:
    Entity(sf::Texture& texture, sf::Vector2f pos_);

    virtual void update() = 0;
    virtual void draw() = 0;
    sf::Sprite& getSprite();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f newPos);
};