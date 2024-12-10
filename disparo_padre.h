#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

class disparo_padre : public sf::Drawable, public collisionable
{
public:
    mutable sf::Sprite sprite;      // Sprite del proyectil
    sf::Texture *texture;    // Textura del proyectil
    float velocidad;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getBounds() const;
    virtual ~disparo_padre();
    int limpiezatotal();


};
