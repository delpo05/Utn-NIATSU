#include "primer_jefe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparos_primer_jefe.h"

primer_jefe::primer_jefe() {

    _texture.loadFromFile("imagen_NIATSU.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect({123, 943, 102, 87});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setPosition(400, -_sprite.getGlobalBounds().height);
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 2;
    disparoTimer = 0;
    vida_jefe =1;
    audiodisparoJefe.loadFromFile("disparojefe1.wav");
    disparoJefe.setBuffer(audiodisparoJefe);
    disparoJefe.setVolume(10);
    audioexplosionJefe.loadFromFile("explosionjefelarga2.wav");
    explosionJefe.setBuffer(audioexplosionJefe);
    explosionJefe.setVolume(10);
    _frame = 0;
    _contador = 0;
    bandera_jefe_muerto = false;
    bufferrecibetiro.loadFromFile("explosion_coli.wav");
    recibetiro.setBuffer(bufferrecibetiro);
    recibetiro.setVolume(10);
    impacto_img = false;

}


void primer_jefe::update() {

    if (impacto_img == true) {
        tiempo_transcurrido_jefe = timerAparicion_jefe.getElapsedTime();
        if (tiempo_transcurrido_jefe.asSeconds() < 0.2) {
            _sprite.setTextureRect({577, 948, 92, 75}); // Frame dañado
        } else {
            _sprite.setTextureRect({123, 943, 102, 87}); // Restaurar textura original
            timerAparicion_jefe.restart();
            impacto_img = false;
        }
    }


    if(bandera_jefe_muerto == false){


    if (vida_jefe <= 0) {
        explosionJefe.play();
        explosion();


    }



    if (std::rand() % 20 == 0) {
        _velocidadX += (std::rand() % 3 - 1);
        if (_velocidadX > 5.0) _velocidadX = 5.0;
        if (_velocidadX < -5.0) _velocidadX = -5.0;
    }


        tiroJ.erase(std::remove_if(tiroJ.begin(), tiroJ.end(), [](disparo_primer_jefe& d)
        {return d.sprite.getPosition().y > 600;}), tiroJ.end());


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
    if (disparoTimer <= 0 && vida_jefe >= 1 && _velocidadY == 0) {
        disparar();
        disparoJefe.play();
        intervaloDisparo = float(std::rand() % 300 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }

    // Actualización de disparos
    for (auto& disparo_primer_jefe :tiroJ) {
        disparo_primer_jefe.update();
    }
}
}



void primer_jefe::disparar() {
    disparo_primer_jefe nuevoDisparo(_sprite.getPosition().x, _sprite.getPosition().y);
    tiroJ.push_back(nuevoDisparo);
}

std::vector<disparo_primer_jefe>& primer_jefe::getDisparos(){
    return tiroJ;
}



void primer_jefe::explosion() {
    _frame += 0.2;

    // Cambia el rectángulo de textura para la animación de explosión
    _sprite.setTextureRect({232 + int(_frame) * 57, 943, 57, 87});

    if (_frame > 5) {
        _frame = 0;
        bandera_jefe_muerto=true;
    }


}



