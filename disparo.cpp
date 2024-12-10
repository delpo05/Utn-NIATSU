#include "disparo.h"


disparo::disparo(float x, float y) {
    texture = new sf::Texture;
    texture ->loadFromFile("disparo.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({140, 183, 65, 40});
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
    sprite.setPosition(x, y);
    velocidad = 10.0;
}

void disparo::update() {
    sprite.move(0, -velocidad);



}


