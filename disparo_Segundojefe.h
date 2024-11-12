#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class disparo_segundo_jefe: public sf::Drawable, public collisionable
{
public:
    sf::Sprite sprite;      // Sprite del proyectil
    sf::Texture *texture;    // Textura del proyectil
    float velocidad;        // Velocidad a la que se mueve el proyectil

    // Constructor del proyectil
    disparo_segundo_jefe (float x, float y);

    // Actualiza la posici�n del proyectil
    void update();

    // Dibuja el proyectil en la ventana
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Obtiene los l�mites (bounds) del proyectil
    sf::FloatRect getBounds() const;
};
