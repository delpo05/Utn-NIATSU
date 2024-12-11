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
    _sprite.setPosition(400, -_sprite.getGlobalBounds().height);
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 2;

    disparoTimer = 0;
    intervaloDisparo = float(std::rand() % 2000 + 1000);
    vida_jefe =15;

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

    ///CHEQUEO DE MEMORY LEAK
    cantidad_de_disparos=0;
}


void Segundo_jefe::update() {

    if (impacto_img) {
        tiempo_transcurrido_jefe = timerAparicion_jefe.getElapsedTime();
        if (tiempo_transcurrido_jefe.asSeconds() < 0.2) {
            _sprite.setTextureRect({656, 219, 94, 124});
        } else {
            _sprite.setTextureRect({118, 205, 112, 130});
            timerAparicion_jefe.restart();
            impacto_img = false;
        }
    }


    if(bandera_jefe_muerto2 == false){

    // Si el enemigo no tiene vida, ejecutar la animación de explosión
    if (vida_jefe <= 0) {
        explosionJefe.play();
        explosion();
         }


    if(_sprite.getPosition().y > _sprite.getGlobalBounds().height){
        bandera_pasoPantalla = true;
    }


        if (std::rand() % 15 == 0) {
            _velocidadX += (std::rand() % 5 - 2);


            if (_velocidadX > 7.0) _velocidadX = 7.0;
            if (_velocidadX < -7.0) _velocidadX = -7.0;
        }


        if (std::rand() % 100 == 0 && bandera_pasoPantalla == true) {
            _velocidadY = (std::rand() % 3 - 1) * 2;
        }


        _sprite.move(_velocidadX, _velocidadY + std::sin(_sprite.getPosition().x / 30.0) * 5);


        if (_sprite.getPosition().x <= 0 || _sprite.getPosition().x >= 800 - _sprite.getGlobalBounds().width) {
            _velocidadX = -_velocidadX;
        }




        if (_sprite.getPosition().y > 600 - _sprite.getGlobalBounds().height) {
            _velocidadY = -1.5f;
        }


        if(_sprite.getPosition().y < _sprite.getGlobalBounds().height && bandera_pasoPantalla == true){
            _sprite.setPosition(_sprite.getPosition().x, _sprite.getGlobalBounds().height);
        }

        if(_sprite.getPosition().y > 200){
            _sprite.setPosition(_sprite.getPosition().x, 200);
        }




        tiroJ.erase(std::remove_if(tiroJ.begin(), tiroJ.end(), [](disparo_segundo_jefe& d) {
            return d.sprite.getPosition().y > 600;
        }), tiroJ.end());



    cantidad_de_disparos = tiroJ.size();


    if (disparoTimer <= 0 && vida_jefe >= 1 && bandera_pasoPantalla == true) {
        disparar();
        disparoJefe.play();
        intervaloDisparo = float(std::rand() % 200 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }


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


    _sprite.setTextureRect({232 + int(_frame) * 57, 943, 57, 87});

    if (_frame > 6 && _contador <= 3) {
        _frame = 0;
        bandera_jefe_muerto2=true;
    }


}

void Segundo_jefe::borrarDisparos(){
    tiroJ.clear();
    cantidad_de_disparos=tiroJ.size();
}

