#pragma once
#include <SFML\Graphics.hpp>
#include "disparo.h"
#include "colision.h"

class Nave: public sf::Drawable, public collisionable
{
        sf::Sprite _sprite;
        sf::Texture _texture;
        float _velocidad;
        std::vector <disparo> disparos;
        int vida_nave;
public:
    Nave();
    void update();
    void disparar();
    const std::vector<disparo>& getDisparos() const;
    sf::FloatRect getBounds() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setVida_nave(int vida){vida_nave=vida;}
    int getVida_nave(){return vida_nave;}

};

