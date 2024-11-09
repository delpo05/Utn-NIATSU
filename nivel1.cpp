#include "Nivel1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

Nivel1::Nivel1() {
    // Inicialización de recursos (sonidos, fuentes, textos, etc.)
    window.create(sf::VideoMode(800, 600), "NIATSU");
    window.setFramerateLimit(60);

    Letra.loadFromFile("Letra.ttf");
    texPuntos.setFont(Letra);
    texvidas.setFont(Letra);
    texVidaJefe1.setFont(Letra);
    texPuntos.setCharacterSize(20);
    texvidas.setCharacterSize(20);
    texVidaJefe1.setCharacterSize(15);

    audiochoque.loadFromFile("audiochoque.wav");
    choque.setBuffer(audiochoque);
    choque.setVolume(10);

    audioshoot.loadFromFile("shoot.wav");
    shoot.setBuffer(audioshoot);

    audioRecibetiro.loadFromFile("RecibeTiro.wav");
    tiroRecibido.setBuffer(audioRecibetiro);

    bufferExplosionColi.loadFromFile("explosion_coli.wav");
    explosionColi.setBuffer(bufferExplosionColi);

    bufferTiroRecibidoJefe.loadFromFile("explosionjefepordisparo.wav");
    tiroRecibidoJefe.setBuffer(bufferTiroRecibidoJefe);

    tiroRecibido.setVolume(7);
    shoot.setVolume(10);
    tiroRecibidoJefe.setVolume(10);
    explosionColi.setVolume(10);

    bandera_oleada = true;
    bandera_jefe_muerto = false;
    puntos = 0;

    // Inicialización de enemigos (colisiones)
    for (int i = 0; i < 3; ++i) {
        colis.emplace_back();
    }

    // Temporizadores
    tiempoDeGracia = 60 * 0.3;
    tiempoDeGracia2 = 60 * 0.5;
    tiempoDeGracia3 = 60 * 0.4;
    tiempoUltimoDisparo = 0.0f;
    intervaloDisparo = 0.2f;
}

void Nivel1::update() {
    // Actualización de objetos
    if (bandera_oleada) {
        fondo.update(1.0 / 60.0f);
        for (auto& coli : colis) {
            coli.update();
        }
    }

    if (bandera_oleada == false) {
        jefe1.update();
    }

    // Actualizar la nave y manejar disparos
    niatsu.update();
    handleDisparos();
    handleCollisions();
    render();
}

void Nivel1::handleCollisions() {
    // COLISIONES VS PRIMER JEFE
    for (auto& disparo : niatsu.getDisparos()) {
        if (disparo.isCollision(jefe1) && !banderaGolpeJefe && !jefe1.getbandera_jefe_muerto()) {
            banderaGolpeJefe = true;
            jefe1.recibedanio();
        }
    }

    if (jefe1.getVida()<1){
        bandera_jefe_muerto=true;
    }

    // COLISIONES VS ENEMIGOS (COLIS)
    if (bandera_oleada) {
        for (auto& disparo : niatsu.getDisparos()) {
            for (auto& coli : colis) {
                if (disparo.isCollision(coli)) {
                    coli.setVida_coli(coli.getVida() - 1);
                    if (coli.getVida() == 0) {
                        // Sumar puntos y reproducir sonido de explosión
                        puntos += 100;
                    }
                    explosionColi.play();
                }
            }
        }
    }

    // CHEQUEO DE COLISIONES DE DISPAROS DE ENEMIGOS CONTRA LA NAVE
    if (bandera_oleada && !banderaGolpe) {
        for (auto& coli : colis) {
            for (auto& disparo_enemigo : coli.getDisparos()) {
                if (disparo_enemigo.isCollision(niatsu)) {
                    banderaGolpe = true;
                    niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                    tiroRecibido.play();
                }
            }
        }
    }

    // Actualización de tiempo de gracia para evitar múltiples colisiones
    if (banderaGolpe) {
        tiempoDeGracia--;
    }

    if (tiempoDeGracia <= 0) {
        tiempoDeGracia = 60 * 0.4;
        banderaGolpe = false;
    }

    // Colisiones de choques entre la nave y los enemigos
    if (bandera_oleada && !bandeChoque) {
        for (auto& coli : colis) {
            if (niatsu.isCollision(coli)) {
                niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                choque.play();
                bandeChoque = true;
                coli.setVida_coli(coli.getVida() - 1);
            }
        }
    }
}

void Nivel1::handleDisparos() {
    // Lógica de disparo intermitente
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (tiempoUltimoDisparo >= intervaloDisparo) {
            niatsu.disparar();
            tiempoUltimoDisparo = 0.0f;
            shoot.play();
        }
    }

    tiempoUltimoDisparo += 1.0 / 60.0;
}

void Nivel1::render() {
    // Renderizar los elementos
    window.clear();
    fondo.draw(window);

    texPuntos.setString("PUNTOS: " + std::to_string(puntos));
    texvidas.setString("VIDAS: " + std::to_string(niatsu.getVida_nave()));
    texVidaJefe1.setString("VIDAS JEFE: " + std::to_string(jefe1.getVida()));

    texPuntos.setPosition({800 - texPuntos.getGlobalBounds().width, 0});
    texVidaJefe1.setPosition({400 - texVidaJefe1.getGlobalBounds().width / 2, 0});

    window.draw(texPuntos);
    window.draw(texvidas);
    if (!bandera_oleada && !jefe1.getbandera_jefe_muerto()) {
        window.draw(texVidaJefe1);
    }

    window.draw(niatsu);

    // Dibujar disparos
    for (auto& disparo : niatsu.getDisparos()) {
        window.draw(disparo);
    }

    if (bandera_oleada) {
        for (auto& coli : colis) {
            window.draw(coli);
            for (auto& disparo : coli.getDisparos()) {
                window.draw(disparo);
            }
        }
    }

    if (!bandera_oleada && !jefe1.getbandera_jefe_muerto()) {
        window.draw(jefe1);
        for (auto& disparo : jefe1.getDisparos()) {
            window.draw(disparo);
        }
    }

    window.display();
}
