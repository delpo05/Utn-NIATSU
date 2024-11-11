#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class Disparo_enemigo: public sf::Drawable, public collisionable
{
public:
    mutable sf::Sprite sprite;      // Sprite del proyectil
    sf::Texture *texture;    // Textura del proyectil
    float velocidad;        // Velocidad a la que se mueve el proyectil

    // Constructor del proyectil
    Disparo_enemigo(float x, float y);

    // Actualiza la posición del proyectil
    void update();

    // Dibuja el proyectil en la ventana
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Obtiene los límites (bounds) del proyectil
    sf::FloatRect getBounds() const;

    void disparo2do () const;


};
