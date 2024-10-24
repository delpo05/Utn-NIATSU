#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "disparo.h"

class Nave: public sf::Drawable
{
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _velocidad;
        std::vector <disparo> disparos;
public:
    Nave();
    void update();
    void disparar();
    const std::vector<disparo>& getDisparos() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

