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
