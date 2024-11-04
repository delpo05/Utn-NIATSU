#include "Fondo.h"

Fondo::Fondo() : velocidad(100.0f), posicionY(0) {
    texturaFondo.loadFromFile("fondo espacio.png");
    texturaFondo.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 800, 1200)); // Dos veces la altura de la imagen para el desplazamiento
}

void Fondo::update(float deltaTime) {
    // Desplaza el fondo hacia abajo
    posicionY += velocidad * deltaTime;

    // Reinicia la posición cuando el fondo sale de la pantalla
    if (posicionY >= 600) {
        posicionY = 0;
    }

    // Actualiza la textura en función de la posiciónY
    spriteFondo.setTextureRect(sf::IntRect(0, static_cast<int>(posicionY), 800, 1200));
}

void Fondo::render(sf::RenderWindow& window) {
    window.draw(spriteFondo);
}
