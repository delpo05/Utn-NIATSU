#include "disparo.h"
//lore
// Constructor del disparo
disparo::disparo(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("disparo.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({210,275,100,60});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height);
    sprite.setPosition(x, y);
    velocidad = 10.0f; // Velocidad de movimiento del disparo
}

// Actualizar posición del disparo
void disparo::update() {
    sprite.move(0, -velocidad); // Movimiento hacia arriba
}

// Dibujar el disparo
void disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);

}
// Obtener los límites del disparo (para colisiones)
sf::FloatRect disparo::getBounds() const {
    return sprite.getGlobalBounds();
}
