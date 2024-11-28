#include "disparos_primer_jefe.h"
//lore
// Constructor del disparo
disparo_primer_jefe::disparo_primer_jefe(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({40,923,35,32});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 10.0; // Velocidad de movimiento del disparo
}

