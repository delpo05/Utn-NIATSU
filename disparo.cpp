#include "disparo.h"

// Constructor del disparo
disparo::disparo(float x, float y) {
    textureDisparo = new sf::Texture;  // Reserva memoria para la textura
    textureDisparo ->loadFromFile("disparo.png");  // Carga la textura desde archivo
    sprite.setTexture(*textureDisparo); // Asigna la textura al sprite
    sprite.setTextureRect({140, 183, 65, 40}); // Rectángulo de textura
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
    sprite.setPosition(x, y); // Posición inicial
    velocidad = 10.0; // Velocidad de movimiento
}

void disparo::update() {
    sprite.move(0, -velocidad); // Movimiento hacia arriba



}

void disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states); // Dibuja el proyectil
}

sf::FloatRect disparo::getBounds() const {
    return sprite.getGlobalBounds(); // Retorna límites para colisiones
}



