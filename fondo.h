#ifndef FONDO_H
#define FONDO_H

#include <SFML/Graphics.hpp>

class Fondo {
public:
    Fondo();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void cambiarFondo (bool secondLevel);

private:
    sf::Texture texturaFondo;
    sf::Texture texturaFondo2;
    sf::Sprite spriteFondo;
    float velocidad;
    float posicionY;
};

#endif // FONDO_H
