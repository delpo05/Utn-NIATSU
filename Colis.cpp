#include "Colis.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>

Colis::Colis ()
{
     _texture.loadFromFile("nave.png");
     _sprite.setTexture (_texture);
     _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height/2);
     ///_sprite.setPosition(rand()% 800, 0);
     ///_velocidad = 8;
}

void Colis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
     target.draw(_sprite, states);
}

void Colis::update()
{
    timesRespawn--;

    if (_newPosition.x > _sprite.getPosition().x) {
    _sprite.move(5, 0);
}

if (_newPosition.x < _sprite.getPosition().x) {
    _sprite.move(-5, 0);
}

if (_newPosition.y > _sprite.getPosition().y) {
    _sprite.move(0, 5);
}

if (_newPosition.y < _sprite.getPosition().y) {
    _sprite.move(0, -5);
}

if (std::abs(_newPosition.x - _sprite.getPosition().x) <= 5) {
    _sprite.setPosition(_newPosition.x, _sprite.getPosition().y);
    _newPosition = { std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 +_sprite.getGlobalBounds().height};
}

if (std::abs(_newPosition.y - _sprite.getPosition().y) <= 5) {
    _sprite.setPosition(_sprite.getPosition().x, _newPosition.y);
    _newPosition = { std::rand() % 700 + _sprite.getGlobalBounds().width, std::rand() % 500 +_sprite.getGlobalBounds().height};
}



}

void Colis::respawn()
{
    _sprite.setPosition(std::rand()%700+ _sprite.getGlobalBounds().width, std::rand()%500+ _sprite.getGlobalBounds().height);
    timesRespawn = 60*5;
}

sf::FloatRect Colis::getBounds() const{
    return _sprite.getGlobalBounds();
}

