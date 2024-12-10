#include "disparo_Segundojefe.h"

disparo_segundo_jefe::disparo_segundo_jefe(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({7,182,97,48});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 10.0;
}




void disparo_segundo_jefe::update() {
    sprite.move(0, velocidad);
}

