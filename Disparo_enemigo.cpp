#include "Disparo_enemigo.h"

// Constructor del disparo
Disparo_enemigo::Disparo_enemigo(float x, float y) {
    texture = new sf::Texture;
    texture->loadFromFile("imagen_NIATSU.png");
    sprite.setTexture(*texture);
    sprite.setTextureRect({50,360,15,30});
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height-10);
    sprite.setPosition(x, y);
    velocidad = 5.0; // Velocidad de movimiento del disparo
}



// Actualizar posici�n del disparo
void Disparo_enemigo::update() {
    sprite.move(0, velocidad); // Movimiento hacia arriba
}


void Disparo_enemigo::disparo2do () const{

     sprite.setTextureRect({23,1278,66,42});

}


