#include "Fondo.h"

Fondo::Fondo(){
    texturaFondo.loadFromFile("fondoespacio800x600.jpg");
    texturaFondo.setRepeated(true);
    texturaFondo2.loadFromFile("Fondo2nivel.jpg");
    texturaFondo2.setRepeated(true);
    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setTextureRect(sf::IntRect(0, 0, 800, 1200));
    velocidad = 100.0;
    posicionY = 0;
}

void Fondo::update(float deltaTime) {
    posicionY -= velocidad * deltaTime;

    if (posicionY >= 600) {
        posicionY = 0;
    }

    spriteFondo.setTextureRect(sf::IntRect(0, posicionY, 800, 600));
}

void Fondo::draw(sf::RenderWindow& window) {
    window.draw(spriteFondo);
}

void Fondo::cambiarFondo(bool secondLevel) {
    if (secondLevel) {
        spriteFondo.setTexture(texturaFondo2);
    } else {
        spriteFondo.setTexture(texturaFondo);
    }
}
