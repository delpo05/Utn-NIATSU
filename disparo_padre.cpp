#include "disparo_padre.h"

void disparo_padre::update() {
    sprite.move(0, velocidad); // Movimiento hacia arriba
}

void disparo_padre::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::FloatRect disparo_padre::getBounds() const {
    return sprite.getGlobalBounds();
}

disparo_padre::~disparo_padre() {
    if(sprite.getPosition().y>600){
    delete texture;}
}
