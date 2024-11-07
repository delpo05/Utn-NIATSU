// game.cpp

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"
#include "Nave.h"
#include "Fondo.h" // Incluye el archivo de la clase Fondo
#include "primer_jefe.h"



// Constructor
Game::Game() {
    inicializacion_ventana();  // Inicializa la ventana y carga los elementos
    iniciar_partida(); // Inicia la partida
}

// Inicialización de la ventana y elementos gráficos
void Game::inicializacion_ventana() {
    window.create(sf::VideoMode(800, 600), "NIATSU");
    window.setFramerateLimit(60);
}

// Método principal que ejecuta el juego (game loop)
void Game::iniciar_partida() {
    Musica.openFromFile("Musica.ogg");
    Musica.setLoop(true);
    Musica.setVolume(5);
    Musica.play();
    tiempoDeGracia = 60 * 0.3;
    tiempoDeGracia2 = 60 * 0.5;
    tiempoDeGracia3= 60 * 0.4;
    tiempoUltimoDisparo = 0.0;
    intervaloDisparo = 0.2;
    puntos = 0;
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
    tiroRecibido.setVolume(7);
    shoot.setVolume(10);
    explosionColi.setVolume(10);
    bandera_oleada = true;
    MenuIntermedio menui(window);

    // Temporizador para controlar la aparición de enemigos
    timerAparicion.restart();

    // Inicialización de enemigos antes del bucle
    for (int i = 0; i < 3; ++i) {
        colis.emplace_back();
    }

    // INICIO DE BUCLE
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Verificar tiempo transcurrido y actualizar bandera para aparición de enemigos
        tiempo_transcurrido = timerAparicion.getElapsedTime();
        if (tiempo_transcurrido.asSeconds() > 20) {
            bandera_oleada = false;
        }
        // APARICION DE JEFE


        // DISPARO INTERMITENTE CON EL ESPACIO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (tiempoUltimoDisparo >= intervaloDisparo) {
                niatsu.disparar();
                tiempoUltimoDisparo = 0.0f;
                shoot.play();
            }
        }

        tiempoUltimoDisparo += 1.0 / 60.0;

        //COLISIONES VS PRIMER JEFE
    for(auto& disparo : niatsu.getDisparos()){
        if(disparo.isCollision(jefe1) && banderaGolpeJefe == false && jefe1.getbandera_jefe_muerto()==false) {
                        banderaGolpeJefe = true;
                        jefe1.setVida_primer_jefe(jefe1.getVida() - 1);
                        explosionColi.play();


        }}




    for(auto& disparo_primer_jefe : jefe1.getDisparos()){
        if(disparo_primer_jefe.isCollision(niatsu)&& banderaGolpe==false && jefe1.getbandera_jefe_muerto()==false){
                        banderaGolpe = true;
                        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                        tiroRecibido.play();
        }
    }





        //FIN DE COLISIONES PRIMER JEFE

        //MENU INTERMEDIO ENTRE MUERTE DE PRIMER JEFE

        if(jefe1.getbandera_jefe_muerto()==true){

        menui.mostrarMenuPrincipal();
        int opcion = menui.getOpcionSeleccionada();
            if (opcion == 0) {

            } else if (opcion == 1) {
            window.close();
                }
        }

        // Actualizar colisiones de disparos con enemigos si bandera_ejemplo es verdadera
        if (bandera_oleada == true) {
            for (auto& disparo : niatsu.getDisparos()) {
                for (auto& coli : colis) {
                    if (disparo.isCollision(coli)) {
                        coli.setVida_coli(coli.getVida() - 1);
                        if(coli.getVida()==0){
                            puntos += 100;
                        }
                        explosionColi.play();
                    }
                }
            }
        }

        // CHEQUEO COLISIONES DISPARO ENEMIGO HACIA NIATSU
        if (bandera_oleada == true && banderaGolpe == false) {
            for (auto& coli : colis) {
                for (auto& Disparo_enemigo : coli.getDisparos()) {
                    if (Disparo_enemigo.isCollision(niatsu)) {
                        banderaGolpe = true;
                        niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                        tiroRecibido.play();
                    }
                }
            }
        }

        if (banderaGolpe == true) {
            tiempoDeGracia--;
        }



        if (tiempoDeGracia <= 0) {
            tiempoDeGracia = 60 * 0.4;
            banderaGolpe = false;
        }

        if (bandeChoque == true) {
            tiempoDeGracia2--;
        }



        if (tiempoDeGracia2 <= 0) {
            tiempoDeGracia2 = 60 * 0.5;
            bandeChoque = false;
        }


        if (banderaGolpeJefe == true) {
            tiempoDeGracia3--;
        }



        if (tiempoDeGracia3 <= 0) {
            tiempoDeGracia3 = 60 * 0.4;
            banderaGolpeJefe = false;
        }






        // CHOQUES
        if (bandera_oleada == true && bandeChoque == false) {
            for (auto& coli : colis) {
                if (niatsu.isCollision(coli)) {
                    niatsu.setVida_nave(niatsu.getVida_nave() - 1);
                    choque.play();
                    bandeChoque = true;
                    coli.setVida_coli(coli.getVida() - 1);

                }
            }
        }

        // INICIO DE UPDATES
        niatsu.update();

        if (bandera_oleada == true){
        fondo.update(1.0 / 60.0f); // Actualiza el fondo con deltaTime
        }

        if (bandera_oleada == true) {
            for (auto& coli : colis) {
                coli.update();
            }
        }

         if (bandera_oleada == false && jefe1.getbandera_jefe_muerto()==false){

            jefe1.update();
            }

        window.clear();

        fondo.draw(window); // Renderiza el fondo

        texPuntos.setPosition({800 - texPuntos.getGlobalBounds().width, 0});
        texVidaJefe1.setPosition({400- texVidaJefe1.getGlobalBounds().width/2 ,0});
        texPuntos.setString("PUNTOS: " + std::to_string(puntos));
        texvidas.setString("VIDAS: " + std::to_string(niatsu.getVida_nave()));
        texVidaJefe1.setString("VIDAS JEFE: " + std::to_string(jefe1.getVida()));

        if(bandera_oleada == false && jefe1.getbandera_jefe_muerto()==false){
            window.draw(texVidaJefe1);
        }


        window.draw(texvidas);
        window.draw(texPuntos);

        for (auto& disparo : niatsu.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);
        }



        if (bandera_oleada == true) {
            for (auto& coli : colis) {
                for (auto& disparo : coli.getDisparos()) {
                    disparo.draw(window, sf::RenderStates::Default);
                }
            }
        }

        if (bandera_oleada == true) {
            for (const auto& coli : colis) {
                window.draw(coli);
            }
        }

                if (bandera_oleada == false && jefe1.getVida()>0) {
                for (auto& disparo : jefe1.getDisparos()) {
                    disparo.draw(window, sf::RenderStates::Default);
                }
        }


         if (bandera_oleada == false){
                window.draw(jefe1);
            }

        window.draw(niatsu);
        window.display();
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar elementos adicionales si es necesario
}

