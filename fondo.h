#ifndef FONDO_H
#define FONDO_H

#include <SFML/Graphics.hpp>

class Fondo {
public:
    Fondo();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    float velocidad;
    float posicionY;
};

#endif // FONDO_H
