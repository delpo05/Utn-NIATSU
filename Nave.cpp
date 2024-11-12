#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"

Nave::Nave()
{
    _velocidad = 6;  // Establece la velocidad de la nave
    _texture.loadFromFile("Nave.png");  // Carga la textura de la nave
    _sprite.setTexture(_texture);  // Asigna la textura al sprite
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height); // Centra el sprite
    vida_nave = 100; // Inicializa la vida de la nave
    _sprite.setPosition(400, 550); // Posición inicial de la nave
}

void Nave::update()
{
    if (vida_nave > 0) {
        // Movimiento de la nave mediante teclas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _sprite.move(0, -_velocidad);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _sprite.move(-_velocidad, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _sprite.move(0, _velocidad);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _sprite.move(_velocidad, 0);

        // Actualiza la posición de cada disparo
        for (auto& disparo : tiro) {
            disparo.update();
        }

        // Eliminar disparos que salen de la pantalla
        tiro.erase(std::remove_if(tiro.begin(), tiro.end(), [](disparo& d)
            {return d.sprite.getPosition().y < 0;}), tiro.end());
        //FIN DE LA ELIMINACION

        // Límites de pantalla para la nave
        if (_sprite.getGlobalBounds().left < 0)
            _sprite.setPosition(_sprite.getOrigin().x, _sprite.getPosition().y);
        if (_sprite.getGlobalBounds().top < 0)
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getOrigin().y);
        if (_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 600)
            _sprite.setPosition(_sprite.getPosition().x, 600 + (_sprite.getGlobalBounds().height - _sprite.getOrigin().y));
        if (_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 800)
            _sprite.setPosition(800 - (_sprite.getGlobalBounds().width - _sprite.getOrigin().x), _sprite.getPosition().y);
    }
}

void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);  // Dibuja la nave en pantalla
}

void Nave::disparar() {
    // Cada disparo se agrega dinámicamente al vector de disparos
    disparo nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    tiro.push_back(nuevoDisparo);
}

const std::vector<disparo>& Nave::getDisparos() const {
    return tiro;
}

sf::FloatRect Nave::getBounds() const {
    return _sprite.getGlobalBounds(); // Obtiene los límites para colisiones
}


