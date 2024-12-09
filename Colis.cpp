#include "Colis.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "Disparo_enemigo.h"

Colis::Colis() {
    _texture = new sf::Texture;
    _texture->loadFromFile("imagen_NIATSU.png");
    _sprite.setTexture(*_texture);
    _sprite.setTextureRect({145, 382, 55, 45});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);

    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 1.5 + float(std::rand() % 200) / 100.0;

    disparoTimer = 0;
    vida_coli = 1;

    audiotiroColi.loadFromFile("Disparocolis.wav");
    tiroColi.setBuffer(audiotiroColi);
    tiroColi.setVolume(1);
    _CantidadColis = 0;
    _frame = 0;
    banderaSegundoNivel = false;
    banderaAparicionSegundosColis = false;
    cant=0;
}

void Colis::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void Colis::update() {
    if (vida_coli <= 0) {
        explosion();

    }

    if (!banderaSegundoNivel) {
        // Comportamiento básico del enemigo
        if (std::rand() % 20 == 0) {
            _velocidadX += (std::rand() % 3 - 1);
            if (_velocidadX > 5.0) _velocidadX = 5.0;
            if (_velocidadX < -5.0) _velocidadX = -5.0;
        }

        _sprite.move(_velocidadX, _velocidadY);

        if (_sprite.getPosition().x <= 0 || _sprite.getPosition().x >= 800 - _sprite.getGlobalBounds().width) {
            _velocidadX = -_velocidadX;
        }

        if (_sprite.getPosition().y > 600) {
            respawn();
        }

        if (disparoTimer <= 0 && vida_coli >= 1) {
            disparar();
            tiroColi.play();
            intervaloDisparo = float(std::rand() % 700 + 100);
            disparoTimer = intervaloDisparo;
        } else {
            disparoTimer -= 10;
        }

        for (auto& disparo : tiroC) {
            disparo.update();
        }
    } else {
        if(banderaAparicionSegundosColis == false){
        _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);
        banderaAparicionSegundosColis = true;
        }
        // Comportamiento avanzado del enemigo en el segundo nivel
        if (std::rand() % 10 == 0) {
            _velocidadX += (std::rand() % 5 - 2);  // Movimiento más errático
            if (_velocidadX > 7.0) _velocidadX = 7.0; // Mayor velocidad
            if (_velocidadX < -7.0) _velocidadX = -7.0;
        }

        _sprite.move(_velocidadX, _velocidadY * 1.5); // Aumento de velocidad vertical también

        if (_sprite.getPosition().x <= 0 || _sprite.getPosition().x >= 800 - _sprite.getGlobalBounds().width) {
            _velocidadX = -_velocidadX;
        }

        if (_sprite.getPosition().y > 600) {
            respawn();
        }

        // Disparo en ráfagas
        if (disparoTimer <= 0 && vida_coli >= 1) {

                disparar();
                tiroColi.play();

            intervaloDisparo = 500;  // Intervalo más corto entre ráfagas
            disparoTimer = intervaloDisparo;
        } else {
            disparoTimer -= 10;
        }

        for (auto& disparo : tiroC) {
            disparo.update();
        }
    }

    // Elimina disparos fuera de la pantalla
    tiroC.erase(std::remove_if(tiroC.begin(), tiroC.end(), [](Disparo_enemigo& d) {
        return d.sprite.getPosition().y > 600;
    }), tiroC.end());


    cant=tiroC.size();
}

void Colis::respawn() {
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 1.5 + float(std::rand() % 200) / 100.0;
    _sprite.setTextureRect({145, 382, 55, 45});
    vida_coli = 1;
}

void Colis::disparar() {
    Disparo_enemigo nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    tiroC.push_back(nuevoDisparo);
}

const std::vector<Disparo_enemigo>& Colis::getDisparos() const {
    return tiroC;
}

sf::FloatRect Colis::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Colis::explosion() {
    _frame += 0.2;
    _sprite.setTextureRect({255 + int(_frame) * 55, 382, 55, 45});

    if (_frame > 6) {
        _frame = 0;
        respawn();
    }
}

void Colis::coli2donivel() {
    _sprite.setTextureRect({138, 1291, 67, 71});
    banderaSegundoNivel = true;
}

void Colis::borrarDisparos(){
    tiroC.clear();
    cant=tiroC.size();
}
