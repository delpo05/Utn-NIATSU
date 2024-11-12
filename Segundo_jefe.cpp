#include "Segundo_jefe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo_Segundojefe.h"

Segundo_jefe::Segundo_jefe() {
    _texture = new sf::Texture;
    _texture->loadFromFile("imagen_NIATSU.png");
    _sprite.setTexture(*_texture);
    _sprite.setTextureRect({118, 205, 112, 130});
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    // Establece la posición inicial en una coordenada aleatoria en la parte superior de la pantalla
    _sprite.setPosition(400, -_sprite.getGlobalBounds().height);

    // Velocidades iniciales aleatorias en X y Y
    _velocidadX = (std::rand() % 2 == 0) ? 3.5 : -3.5;
    _velocidadY = 2;

    disparoTimer = 0;
    intervaloDisparo = float(std::rand() % 2000 + 1000);  // entre 1 y 3 segundos
    vida_segundo_jefe =10;

    audiodisparoJefe.loadFromFile("disparojefe1.wav");
    disparoJefe.setBuffer(audiodisparoJefe);
    disparoJefe.setVolume(10);

    audioexplosionJefe.loadFromFile("explosionjefelarga2.wav");
    explosionJefe.setBuffer(audioexplosionJefe);
    explosionJefe.setVolume(10);



    _frame = 0;
    _contador = 0;
    bandera_jefe_muerto2 = false;

    bufferrecibetiro.loadFromFile("explosion_coli.wav");
    recibetiro.setBuffer(bufferrecibetiro);
    recibetiro.setVolume(10);

    impacto_img = false;

}

void Segundo_jefe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void Segundo_jefe::update() {

    if (impacto_img) {
        tiempo_transcurrido_jefe2 = timerAparicion_jefe2.getElapsedTime();
        if (tiempo_transcurrido_jefe2.asSeconds() < 0.2) {
            _sprite.setTextureRect({577, 948, 92, 75}); // Frame dañado
        } else {
            _sprite.setTextureRect({118, 205, 112, 130}); // Restaurar textura original
            timerAparicion_jefe2.restart();
            impacto_img = false;
        }
    }


    if(bandera_jefe_muerto2 == false){

    // Si el enemigo no tiene vida, ejecutar la animación de explosión
    if (vida_segundo_jefe <= 0) {
        explosionJefe.play();
        explosion();

         // Detener la actualización si está explotando
    }


    // Ajuste aleatorio en la velocidad X para un movimiento horizontal más impredecible
    if (std::rand() % 20 == 0) {  // 1 en 20 posibilidad de cambiar aleatoriamente cada ciclo
        _velocidadX += (std::rand() % 3 - 1);  // Añade -1, 0 o 1 a _velocidadX
        if (_velocidadX > 5.0) _velocidadX = 5.0; // Límite superior
        if (_velocidadX < -5.0) _velocidadX = -5.0; // Límite inferior
    }


        tiroJ.erase(std::remove_if(tiroJ.begin(), tiroJ.end(), [](disparo_segundo_jefe& d)
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
    if (disparoTimer <= 0 && vida_segundo_jefe >= 1 && _velocidadY == 0) {
        disparar();
        disparoJefe.play();
        intervaloDisparo = float(std::rand() % 500 + 100);
        disparoTimer = intervaloDisparo;
    } else {
        disparoTimer -= 10;
    }

    // Actualización de disparos
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

sf::FloatRect Segundo_jefe::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Segundo_jefe::explosion() {
    _frame += 0.2;

    // Cambia el rectángulo de textura para la animación de explosión
    _sprite.setTextureRect({232 + int(_frame) * 57, 943, 57, 87});

    if (_frame > 6 && _contador <= 3) {
        _frame = 0;
        bandera_jefe_muerto2=true;
    }


}

void Segundo_jefe::recibedanio(){
    setVida_segundo_jefe(getVida()-1);
    impacto_img = true;
    timerAparicion_jefe2.restart(); // Inicia el temporizador en cada impacto
    recibetiro.play();

}

