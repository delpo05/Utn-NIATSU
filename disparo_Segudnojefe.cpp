#include "disparo_Segundojefe.h"
//lore
// Constructor del disparo
disparo_segundo_jefe::disparo_segundo_jefe(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({7,182,97,48});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 10.0; // Velocidad de movimiento del disparo
}




void disparo_segundo_jefe::update() {
    sprite.move(0, velocidad); // Movimiento hacia arriba
}

