#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"
class bonus : public sf::Drawable, public collisionable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
public:
    bonus();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void respawn();
    sf::FloatRect getBounds() const;
};
