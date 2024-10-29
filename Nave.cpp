#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"


Nave::Nave()
{
    _velocidad = 10;
    _texture.loadFromFile("Nave.png");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, _sprite.getGlobalBounds().height);
    vida_nave = 1000;


}

void Nave::update()
{

    if(vida_nave > 0){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _sprite.move(0,-_velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            _sprite.move(-_velocidad,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _sprite.move(0,_velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _sprite.move(_velocidad,0);
        }


         for (auto& disparo : disparos) { //actualiza pos de disparo
            disparo.update();
        }

                // Eliminar disparos fuera de la pantalla
        disparos.erase(std::remove_if(disparos.begin(), disparos.end(), [](disparo& d) {
            return d.sprite.getPosition().y < 0;  // Si sale de la pantalla
            }), disparos.end());



        if(_sprite.getGlobalBounds().left<0){
            _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
            //_velocidad.x = -_velocidad.x;
        }
        if(_sprite.getGlobalBounds().top<0){
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
            //_velocidad.y = -_velocidad.y;
        }
        if(_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height>600){
            _sprite.setPosition(_sprite.getPosition().x,600 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
            //_velocidad.y = -_velocidad.y;

        }
        if(_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width>800){
            _sprite.setPosition(800- (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
            //_velocidad.x = -_velocidad.x;
        }

    }








}


void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);



}

void Nave::disparar(){
        disparo nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
        disparos.push_back(nuevoDisparo);
}

// Obtener disparos
const std::vector<disparo>& Nave::getDisparos() const {
    return disparos;
}


sf::FloatRect Nave::getBounds() const{
    return _sprite.getGlobalBounds();
}









