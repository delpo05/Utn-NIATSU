#include "GAME.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"
#include "Nave.h"

// Constructor
Game::Game() {
    inicializacion_ventana();  // Inicializa la ventana y carga los elementos
    iniciar_partida(); //Inicia la partida

}

// Inicialización de la ventana y elementos gráficos
void Game::inicializacion_ventana() {
    window.create(sf::VideoMode(800, 600), "NIATSU");
    window.setFramerateLimit(60);
    tex.loadFromFile("fondo espacio.jpg");
    fondo.setTexture(tex);

}

// Método principal que ejecuta el juego (game loop)
void Game::iniciar_partida() {
    Musica.openFromFile("Musica.ogg");
    Musica.setLoop(true);
    Musica.setVolume(3);
    Musica.play();
    tiempoDeGracia = 60*1;
    tiempoUltimoDisparo = 0.0;
    intervaloDisparo = 0.2;
    puntos = 0;


    Letra.loadFromFile("Letra.ttf");
    texPuntos.setFont(Letra);
    texPuntos.setCharacterSize(20);
    texvidas.setCharacterSize(20);
    texvidas.setFont(Letra);

    audiochoque.loadFromFile("audiochoque.wav");
    choque.setBuffer(audiochoque);


    audioshoot.loadFromFile("shoot.wav");
    shoot.setBuffer (audioshoot);

     audiotiro.loadFromFile("audiochoque.wav");
     tiro.setBuffer (audiotiro);








    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Detectar disparo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        if(tiempoUltimoDisparo>=intervaloDisparo){
            niatsu.disparar();
            tiempoUltimoDisparo=0.0f;

            shoot.play();
            shoot.setVolume(15);

        }
        }

        tiempoUltimoDisparo += 1.0 / 60.0;

///for de colisiones de vector disparo de colis hacia niatsu
    for (auto& disparo : niatsu.getDisparos()) {

    if (disparo.isCollision(coli1)) {
        coli1.setVida_coli(coli1.getVida() - 1);
        puntos+=100;
    }
    if (disparo.isCollision(coli2)) {
        coli2.setVida_coli(coli2.getVida() - 1);
        puntos+=100;
    }
    if (disparo.isCollision(coli3)) {
        coli3.setVida_coli(coli3.getVida() - 1);
        puntos+=100;
    }

}

///CHEQUEO COLISIONES DISPARO ENEMIGO


if (banderaGolpe == false){
for (auto& Disparo_enemigo : coli1.getDisparos()) {
    if (Disparo_enemigo.isCollision(niatsu)) {
        banderaGolpe = true;
        niatsu.setVida_nave(niatsu.getVida_nave()-1);
        tiro.play();


    }
}}


if (banderaGolpe == false){
for (auto& Disparo_enemigo : coli2.getDisparos()) {
    if (Disparo_enemigo.isCollision(niatsu)) {
        banderaGolpe = true;
        niatsu.setVida_nave(niatsu.getVida_nave()-1);
        tiro.play();
    }
}}


if (banderaGolpe == false){
for (auto& Disparo_enemigo : coli3.getDisparos()) {
    if (Disparo_enemigo.isCollision(niatsu)) {
        banderaGolpe = true;
        niatsu.setVida_nave(niatsu.getVida_nave()-1);
        tiro.play();
    }
}}


if(banderaGolpe==true){
    tiempoDeGracia--;
}

if(tiempoDeGracia<=0){
    tiempoDeGracia=60*1;
    banderaGolpe=false;
}

/// CHOQUES
if (bandeChoque == false) { /// COLI 1
    if (niatsu.isCollision(coli1)) {
        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
        choque.play();
        choque.setVolume(10);
        bandeChoque = true;
        coli1.setVida_coli(coli1.getVida()-1);

    }
}
    else {
    if (!niatsu.isCollision(coli1)) {
        bandeChoque = false;
    }
}

if (bandeChoque == false) {   /// COLI 2
    if (niatsu.isCollision(coli2)) {
        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
        choque.play();
        choque.setVolume(10);
        bandeChoque = true;
        coli2.setVida_coli(coli2.getVida()-1);

    }
}
    else {
    if (!niatsu.isCollision(coli2)) {
        bandeChoque = false;
    }
}

if (bandeChoque == false) {  /// COLI 3
    if (niatsu.isCollision(coli3)) {
        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
        choque.play();
        choque.setVolume(10);
        bandeChoque = true;
        coli3.setVida_coli(coli3.getVida()-1);

    }
}
    else {
    if (!niatsu.isCollision(coli3)) {
        bandeChoque = false;
    }
}

/// FIN DE CHOQUES



        // Actualizar estado del juego
        niatsu.update();
        coli1.update ();
        coli2.update ();
        coli3.update ();

        // Limpiar ventana
        window.clear();

        // Dibujar fondo y nave
        window.draw(fondo);
        texPuntos.setPosition({800- texPuntos.getGlobalBounds().width,0});
        texPuntos.setString("PUNTOS: " +std::to_string(puntos));
        texvidas.setString("VIDAS: "+std::to_string(niatsu.getVida_nave()));
        window.draw(texvidas);
        window.draw(texPuntos);


        // Dibujar disparos
        for (auto& disparo : niatsu.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
        }

        for (auto& disparo : coli1.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
        }

        for (auto& disparo : coli2.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
        }
        for (auto& disparo : coli3.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
        }




        window.draw(coli1);
        window.draw(coli2);
        window.draw(coli3);
        window.draw(niatsu);

        // Actualizar pantalla
        window.display();
    }
}



void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar elementos adicionales si es necesario
}
