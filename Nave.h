#pragma once
#include <SFML\Graphics.hpp>

class Nave: public sf::Drawable
{
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _velocidad;
public:
    Nave();
    void update();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

