#include "Colis.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "Disparo_enemigo.h"

Colis::Colis() {
    _texture.loadFromFile("disparo_enemigo.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({145, 382, 55, 45});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    // Establece la posición inicial en una coordenada aleatoria en la parte superior de la pantalla
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);



    // Velocidades iniciales aleatorias en X y Y
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 1.5 + float(std::rand() % 200) / 100.0;

    disparoTimer = 0;
    intervaloDisparo = float(std::rand() % 2000 + 1000);  // entre 1 y 3 segundos
    vida_coli=1;

    audiotiroColi.loadFromFile("Disparocolis.wav");
    tiroColi.setBuffer(audiotiroColi);
    tiroColi.setVolume(1);
    _CantidadColis = 0;
}

void Colis::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void Colis::update() {
    // Ajuste aleatorio en la velocidad X para un movimiento horizontal más impredecible
    if (std::rand() % 20 == 0) {  // 1 en 20 posibilidad de cambiar aleatoriamente cada ciclo
        _velocidadX += (std::rand() % 3 - 1);  // Añade -1, 0 o 1 a _velocidadX
        if (_velocidadX > 5.0) _velocidadX = 5.0; // Límite superior
        if (_velocidadX < -5.0) _velocidadX = -5.0; // Límite inferior
    }

    // Movimiento
    _sprite.move(_velocidadX, _velocidadY);

    // Cambia la dirección en X si el enemigo toca los bordes de la pantalla
    if (_sprite.getPosition().x <= 0 || _sprite.getPosition().x >= 800 - _sprite.getGlobalBounds().width) {
        _velocidadX = -_velocidadX; // Invierte la dirección en X
    }

    // Desaparece y vuelve a la parte superior si se mueve fuera de la pantalla hacia abajo


    if (_sprite.getPosition().y > 600 || vida_coli <= 0) {
        respawn();
        _CantidadColis++;
    }

    // Control de disparo
    if (disparoTimer <= 0 && vida_coli>=1) {
        disparar();
        tiroColi.play();
        intervaloDisparo = float(std::rand() % 700 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }

    // Actualización de disparos
    for (auto& disparo : disparos) {
        disparo.update();
    }


}

void Colis::respawn() {
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 1.5 + float(std::rand() % 200) / 100.0;
    vida_coli=1;
}

void Colis::disparar() {
    Disparo_enemigo nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    disparos.push_back(nuevoDisparo);
}

const std::vector<Disparo_enemigo>& Colis::getDisparos() const {
    return disparos;
}




sf::FloatRect Colis::getBounds() const {
    return _sprite.getGlobalBounds();
}
