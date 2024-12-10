#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"

Nave::Nave()
{
    _velocidad = 6;
    _texture.loadFromFile("Nave.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
    vida_nave = 20;
    _sprite.setPosition(400, 550);
    cantidad_de_disparos = 0;
}

void Nave::update()
{
    if (vida_nave > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _sprite.move(0, -_velocidad);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _sprite.move(-_velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _sprite.move(0, _velocidad);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _sprite.move(_velocidad, 0);


        for (auto& disparo : tiro) {
            disparo.update();
        }


        tiro.erase(std::remove_if(tiro.begin(), tiro.end(), [](disparo& d)
            {return d.sprite.getPosition().y < 0;}), tiro.end());



        if (_sprite.getGlobalBounds().left < 0)
            _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
        if (_sprite.getGlobalBounds().top < 0)
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
        if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 600)
            _sprite.setPosition(_sprite.getPosition().x, 600 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
        if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800)
            _sprite.setPosition(800 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }


    cantidad_de_disparos = tiro.size();
}

void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Nave::disparar() {
    disparo nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    tiro.push_back(nuevoDisparo);
}

const std::vector<disparo>& Nave::getDisparos() const {
    return tiro;
}

sf::FloatRect Nave::getBounds() const {
    return _sprite.getGlobalBounds();
}


void Nave::borrarDisparos(){
    tiro.clear();
}

