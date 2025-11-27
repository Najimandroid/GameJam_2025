#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f pos_) : sprite(texture), pos(pos_)
{

}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}

sf::Vector2f Entity::getPos()
{
    return pos;
}

void Entity::setPos(sf::Vector2f newPos)
{
    pos = newPos;
}