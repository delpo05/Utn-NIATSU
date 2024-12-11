#pragma once
#include <SFML\Graphics.hpp>
#include "disparo.h"
#include "colision.h"


class Nave: public sf::Drawable, public collisionable
{
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _velocidad;
    std::vector<disparo> tiro;
    int vida_nave;
    size_t cantidad_de_disparos;
public:
    Nave();
    void update();
    void disparar();
    const std::vector<disparo>& getDisparos() const;
    sf::FloatRect getBounds() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setVida_nave(int vida) { vida_nave = vida; }
    int getVida_nave() { return vida_nave; }
    size_t Getcantidad_de_disparos(){return cantidad_de_disparos;};
    void borrarDisparos();
};

