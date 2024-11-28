/*#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"

// La clase disparo representa cada proyectil disparado por la nave
class disparo : public sf::Drawable, public collisionable {

public:
    sf::Sprite sprite;      // Sprite del proyectil
    sf::Texture* textureDisparo;   // Textura del proyectil (memoria dinámica)
    float velocidad;        // Velocidad de movimiento del proyectil



    disparo(float x, float y);  // Constructor
    void update();              // Actualiza la posición
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;  // Dibuja el proyectil
    sf::FloatRect getBounds() const; // Obtiene límites para colisiones
    ~disparo();


};*/


#pragma once
#include <SFML/Graphics.hpp>
#include "colision.h"
#include "disparo_padre.h"

class disparo: public disparo_padre
{
public:
    disparo(float x, float y);
    void update();

};

