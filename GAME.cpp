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
    iniciar_partida(); // Inicia la partida
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
    tiempoDeGracia = 60 * 0.3;
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
    choque.setVolume(10);
    audioshoot.loadFromFile("shoot.wav");
    shoot.setBuffer(audioshoot);
    audioRecibetiro.loadFromFile("RecibeTiro.wav");
    tiroRecibido.setBuffer(audioRecibetiro);
    tiroRecibido.setVolume(7);
    shoot.setVolume(10);

    // Inicialización de los enemigos
    for (int i = 0; i < 3; ++i) {
        colis.emplace_back(); // Agregar un nuevo enemigo al vector
    }

    // INICIO DE BUCLE
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /// DISPARO INTERMITENTE CON EL ESPACIO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (tiempoUltimoDisparo >= intervaloDisparo) {
                niatsu.disparar();
                tiempoUltimoDisparo = 0.0f;
                shoot.play();
            }
        }

        tiempoUltimoDisparo += 1.0 / 60.0;

        /// for de colisiones de vector disparos hacia colis
        for (auto& disparo : niatsu.getDisparos()) {
            for (auto& coli : colis) {  // Iterar sobre cada Colis
                if (disparo.isCollision(coli)) {
                    coli.setVida_coli(coli.getVida() - 1);
                    puntos += 100;
                }
            }
        }

        // CHEQUEO COLISIONES DISPARO ENEMIGO HACIA NIATSU
        if (banderaGolpe == false) {
            for (auto& coli : colis) {  // Iterar sobre cada Colis
                for (auto& Disparo_enemigo : coli.getDisparos()) {
                    if (Disparo_enemigo.isCollision(niatsu)) {
                        banderaGolpe = true;
                        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                        tiroRecibido.play();
                    }
                }
            }
        }

        if (banderaGolpe) {
            tiempoDeGracia--;
        }

        if (tiempoDeGracia <= 0) {
            tiempoDeGracia = 60 * 0.3;
            banderaGolpe = false;
        }

        // CHOQUES
        if (bandeChoque == false) {
            for (auto& coli : colis) {  // Iterar sobre cada Colis
                if (niatsu.isCollision(coli)) {
                    niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                    choque.play();
                    bandeChoque = true;
                    coli.setVida_coli(coli.getVida() - 1);
                    tiroRecibido.play();
                }
            }
        } else {
            for (auto& coli : colis) {
                if (!niatsu.isCollision(coli)) {
                    bandeChoque = false;
                }
            }
        }

        // INICIO DE UPDATES
        // Actualizar estado del juego
        niatsu.update();
        for (auto& coli : colis) {  // Actualizar cada Colis
            coli.update();
        }

        // Limpiar ventana
        window.clear();

        // Dibujar fondo y nave
        window.draw(fondo);
        texPuntos.setPosition({800 - texPuntos.getGlobalBounds().width, 0});
        texPuntos.setString("PUNTOS: " + std::to_string(puntos));
        texvidas.setString("VIDAS: " + std::to_string(niatsu.getVida_nave()));
        window.draw(texvidas);
        window.draw(texPuntos);

        // Dibujar disparos
        for (auto& disparo : niatsu.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
        }

        for (auto& coli : colis) {  // Dibujar disparos de cada Colis
            for (auto& disparo : coli.getDisparos()) {
                disparo.draw(window, sf::RenderStates::Default);  // Pasando los estados por defecto
            }
        }

        // Dibujar enemigos
        for (const auto& coli : colis) {  // Dibujar cada Colis
            window.draw(coli);
        }

        // Dibujar nave
        window.draw(niatsu);

        // Actualizar pantalla
        window.display();
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar elementos adicionales si es necesario
}

