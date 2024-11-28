#include "disparo.h"

// Constructor del disparo
disparo::disparo(float x, float y) {
    texture = new sf::Texture;  // Reserva memoria para la textura
    texture ->loadFromFile("disparo.png");  // Carga la textura desde archivo
    sprite.setTexture(*texture); // Asigna la textura al sprite
    sprite.setTextureRect({140, 183, 65, 40}); // Rectángulo de textura
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
    sprite.setPosition(x, y); // Posición inicial
    velocidad = 10.0; // Velocidad de movimiento
}

void disparo::update() {
    sprite.move(0, -velocidad); // Movimiento hacia arriba



}


