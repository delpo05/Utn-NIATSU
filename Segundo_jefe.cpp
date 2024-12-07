#include "Segundo_jefe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include "disparo_Segundojefe.h"

Segundo_jefe::Segundo_jefe() {

    _texture.loadFromFile("imagen_NIATSU.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({118, 205, 112, 130});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    // Establece la posici�n inicial en una coordenada aleatoria en la parte superior de la pantalla
    _sprite.setPosition(400, -_sprite.getGlobalBounds().height);

    // Velocidades iniciales aleatorias en X y Y
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 2;

    disparoTimer = 0;
    intervaloDisparo = float(std::rand() % 2000 + 1000);  // entre 1 y 3 segundos
    vida_jefe =2;

    audiodisparoJefe.loadFromFile("disparojefe1.wav");
    disparoJefe.setBuffer(audiodisparoJefe);
    disparoJefe.setVolume(10);

    audioexplosionJefe.loadFromFile("explosionjefelarga2.wav");
    explosionJefe.setBuffer(audioexplosionJefe);
    explosionJefe.setVolume(10);



    _frame = 0;
    _contador = 0;
    bandera_jefe_muerto2 = false;
    bandera_pasoPantalla = false;

    bufferrecibetiro.loadFromFile("explosion_coli.wav");
    recibetiro.setBuffer(bufferrecibetiro);
    recibetiro.setVolume(10);

    impacto_img = false;

}


void Segundo_jefe::update() {

    if (impacto_img) {
        tiempo_transcurrido_jefe = timerAparicion_jefe.getElapsedTime();
        if (tiempo_transcurrido_jefe.asSeconds() < 0.2) {
            _sprite.setTextureRect({656, 219, 94, 124}); // Frame da�ado
        } else {
            _sprite.setTextureRect({118, 205, 112, 130}); // Restaurar textura original
            timerAparicion_jefe.restart();
            impacto_img = false;
        }
    }


    if(bandera_jefe_muerto2 == false){

    // Si el enemigo no tiene vida, ejecutar la animaci�n de explosi�n
    if (vida_jefe <= 0) {
        explosionJefe.play();
        explosion();

         // Detener la actualizaci�n si est� explotando
         }


    if(_sprite.getPosition().y > _sprite.getGlobalBounds().height){

        bandera_pasoPantalla = true;

    }

        // Ajuste aleatorio en la velocidad X para un movimiento m�s impredecible
        if (std::rand() % 15 == 0) {  // 1 en 15 posibilidad de cambiar aleatoriamente cada ciclo
            _velocidadX += (std::rand() % 5 - 2);  // A�ade -2, -1, 0, 1 o 2 a _velocidadX

            // Limita _velocidadX entre -7.0 y 7.0
            if (_velocidadX > 7.0) _velocidadX = 7.0;
            if (_velocidadX < -7.0) _velocidadX = -7.0;
        }

        // Movimiento en oleada en Y para patr�n vertical adicional
        if (std::rand() % 100 == 0 && bandera_pasoPantalla == true) {  // Cada cierto tiempo cambia la direcci�n Y
            _velocidadY = (std::rand() % 3 - 1) * 2;  // Cambia a -2, 0 o 2
        }

        // Movimiento del jefe2
        _sprite.move(_velocidadX, _velocidadY + std::sin(_sprite.getPosition().x / 30.0) * 5);

        // Cambia direcci�n en X e Y si el jefe toca los bordes de la pantalla
        if (_sprite.getPosition().x <= 0 || _sprite.getPosition().x >= 800 - _sprite.getGlobalBounds().width) {
            _velocidadX = -_velocidadX; // Invierte la direcci�n en X
        }



        // Condici�n para que el jefe2 vuelva a la velocidad inicial en Y tras pasar cierto l�mite
        if (_sprite.getPosition().y > 600 - _sprite.getGlobalBounds().height) {
            _velocidadY = -1.5f; // Velocidad constante hacia arriba si alcanza el l�mite inferior
        }


        if(_sprite.getPosition().y < _sprite.getGlobalBounds().height && bandera_pasoPantalla == true){
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getGlobalBounds().height);
        }

        if(_sprite.getPosition().y > 200){
            _sprite.setPosition(_sprite.getPosition().x, 200);
        }



        // Elimina proyectiles que salen de la pantalla
        tiroJ.erase(std::remove_if(tiroJ.begin(), tiroJ.end(), [](disparo_segundo_jefe& d) {
            return d.sprite.getPosition().y > 600;
        }), tiroJ.end());


    // Control de disparo
    if (disparoTimer <= 0 && vida_jefe >= 1 && bandera_pasoPantalla == true) {
        disparar();
        disparoJefe.play();
        intervaloDisparo = float(std::rand() % 200 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }

    // Actualizaci�n de disparos
    for (auto& disparo_segundo_jefe :tiroJ) {
        disparo_segundo_jefe.update();
    }
}
}

void Segundo_jefe::disparar() {
    disparo_segundo_jefe nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    tiroJ.push_back(nuevoDisparo);
}

const std::vector<disparo_segundo_jefe>& Segundo_jefe::getDisparos() const {
    return tiroJ;
}

void Segundo_jefe::explosion() {
    _frame += 0.2;

    // Cambia el rect�ngulo de textura para la animaci�n de explosi�n
    _sprite.setTextureRect({232 + int(_frame) * 57, 943, 57, 87});

    if (_frame > 6 && _contador <= 3) {
        _frame = 0;
        bandera_jefe_muerto2=true;
    }


}

