#include "Fondo.h"

Fondo::Fondo(){
    texturaFondo.loadFromFile("fondo espacio.jpg");
    texturaFondo.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 800, 1200)); // Dos veces la altura de la imagen para el desplazamiento
    velocidad = 100.0;
    posicionY = 0;
}

void Fondo::update(float deltaTime) {
    // Desplaza el fondo hacia abajo
    posicionY -= velocidad * deltaTime;

    // Reinicia la posici�n cuando el fondo sale de la pantalla
    if (posicionY >= 600) {
        posicionY = 0;
    }

    // Actualiza la textura en funci�n de la posici�nY
    spriteFondo.setTextureRect(sf::IntRect(0, posicionY, 800, 1200));
}

void Fondo::draw(sf::RenderWindow& window) {
    window.draw(spriteFondo);
}