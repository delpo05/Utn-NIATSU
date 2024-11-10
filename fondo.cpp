#include "Fondo.h"

Fondo::Fondo(){
    texturaFondo.loadFromFile("fondo espacio.jpg");
    texturaFondo.setRepeated(true);
    texturaFondo2.loadFromFile("image.jpg"); //Fondo 2do nivel
    texturaFondo2.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 800, 1200)); // Dos veces la altura de la imagen para el desplazamiento
    velocidad = 100.0;
    posicionY = 0;
}

void Fondo::update(float deltaTime) {
    // Desplaza el fondo hacia abajo
    posicionY -= velocidad * deltaTime;

    // Reinicia la posición cuando el fondo sale de la pantalla
    if (posicionY >= 600) {
        posicionY = 0;
    }

    // Actualiza la textura en función de la posiciónY
    spriteFondo.setTextureRect(sf::IntRect(0, posicionY, 800, 1200));
}

void Fondo::draw(sf::RenderWindow& window) {
    window.draw(spriteFondo);
}

void Fondo::cambiarFondo(bool secondLevel) {
    if (secondLevel) {
        // Cambiar a fondo del segundo nivel
        spriteFondo.setTexture(texturaFondo2);
    } else {
        // Cambiar a fondo del primer nivel
        spriteFondo.setTexture(texturaFondo);
    }
}
