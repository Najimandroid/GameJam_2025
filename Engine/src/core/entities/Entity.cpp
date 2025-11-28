#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f pos_) : sprite(texture), pos(pos_)
{
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 32 }));
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
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

sf::FloatRect Entity::GetBounds() const
{
    return sprite.getGlobalBounds();
}