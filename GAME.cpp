#include "Game.h"
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
    Musica.setVolume(5);
    Musica.play();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Detectar disparo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            niatsu.disparar();

        }






    for (auto& disparo : niatsu.getDisparos()) {
    if (disparo.isCollision(coli1)) {
        coli1.setVida_coli(coli1.getVida() - 1);
    }
    if (disparo.isCollision(coli2)) {
        coli2.setVida_coli(coli2.getVida() - 1);
    }
    if (disparo.isCollision(coli3)) {
        coli3.setVida_coli(coli3.getVida() - 1);
    }
}







        // Actualizar estado del juego
        niatsu.update();
        coli1.update ();
        coli2.update ();
        coli3.update ();

        // Limpiar ventana
        window.clear();

        // Dibujar fondo y nave
        window.draw(fondo);


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
