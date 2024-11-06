#include "primer_jefe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparos_primer_jefe.h"

primer_jefe::primer_jefe() {
    _texture = new sf::Texture;
    _texture->loadFromFile("colis.png");
    _sprite.setTexture(*_texture);
    _sprite.setTextureRect({123, 943, 102, 87});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    // Establece la posición inicial en una coordenada aleatoria en la parte superior de la pantalla
    _sprite.setPosition(400, -_sprite.getGlobalBounds().height);

    // Velocidades iniciales aleatorias en X y Y
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 2;

    disparoTimer = 0;
    intervaloDisparo = float(std::rand() % 2000 + 1000);  // entre 1 y 3 segundos
    vida_primer_jefe = 20;

    audiotiroColi.loadFromFile("Disparocolis.wav");
    tiroColi.setBuffer(audiotiroColi);
    tiroColi.setVolume(1);

    _frame = 0;
    _contador = 0;
    bandera_jefe_muerto = false;
}

void primer_jefe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void primer_jefe::update() {

    if(bandera_jefe_muerto == false){

    // Si el enemigo no tiene vida, ejecutar la animación de explosión
    if (vida_primer_jefe <= 0) {
        explosion();
         // Detener la actualización si está explotando
    }


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

    if(_sprite.getPosition().y > _sprite.getGlobalBounds().height){
        _velocidadY = 0;
    }

    // Desaparece y vuelve a la parte superior si se mueve fuera de la pantalla hacia abajo
    /*if (_sprite.getPosition().y > 600) {
        respawn();
    }*/

    // Control de disparo
    if (disparoTimer <= 0 && vida_primer_jefe >= 1 && _velocidadY == 0) {
        disparar();
        tiroColi.play();
        intervaloDisparo = float(std::rand() % 500 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }

    // Actualización de disparos
    for (auto& disparo : disparos) {
        disparo.update();
    }
}
}

/*void Colis::respawn() {
    _sprite.setPosition(std::rand() % 700 + _sprite.getGlobalBounds().width, -_sprite.getGlobalBounds().height);
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 1.5 + float(std::rand() % 200) / 100.0;
    _sprite.setTextureRect({145, 382, 55, 45});
    vida_coli = 1; // Reinicia la vida del enemigo
}*/

void primer_jefe::disparar() {
    disparo_primer_jefe nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    disparos.push_back(nuevoDisparo);
}

const std::vector<disparo_primer_jefe>& primer_jefe::getDisparos() const {
    return disparos;
}

sf::FloatRect primer_jefe::getBounds() const {
    return _sprite.getGlobalBounds();
}

void primer_jefe::explosion() {
    _frame += 0.2;

    // Cambia el rectángulo de textura para la animación de explosión
    _sprite.setTextureRect({232 + int(_frame) * 57, 943, 57, 87});

    if (_frame > 6 && _contador <= 3) {
        _frame = 0;
        bandera_jefe_muerto=true;
    }


}

