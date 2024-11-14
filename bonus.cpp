#include "bonus.h"
#include <stdlib.h>

bonus::bonus()
{
    _texture.loadFromFile("bonus.png");
    _sprite.setTexture(_texture);

}


void bonus::update()
{
    _sprite.move(0,3);
}


void bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void bonus::respawn()
{
    _sprite.setPosition(std::rand()%700+ _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);
}

sf::FloatRect bonus::getBounds() const{
    return _sprite.getGlobalBounds();
}
