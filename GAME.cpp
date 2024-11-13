///game.cpp
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "disparo.h"
#include "Nave.h"
#include "Fondo.h"  // Incluye el archivo de la clase Fondo
#include "primer_jefe.h"
#include "archivo_jugadores.h"

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
    MenuIntermedio menui(window);
    Musica.openFromFile("Musica.ogg");
    Musica.setLoop(true);
    Musica.setVolume(5);
    Musica.play();

    // Inicialización de tiempos y variables
    tiempoDeGracia = 60 * 0.3;
    tiempoDeGracia2 = 60 * 0.5;
    tiempoDeGracia3 = 60 * 0.4;
    tiempoUltimoDisparo = 0.0f;
    tiempoOleada = 5;
    tiempoOleada2 = 5;
    intervaloDisparo = 0.2f;
    puntos = 0;

    // Cargar fuentes
    Letra.loadFromFile("Letra.ttf");
    texPuntos.setFont(Letra);
    texvidas.setFont(Letra);
    texVidaJefe1.setFont(Letra);
    texVidaJefe2.setFont(Letra);
    texOleada.setFont(Letra);
    texPuntos.setCharacterSize(20);
    texvidas.setCharacterSize(20);
    texVidaJefe1.setCharacterSize(15);
    texVidaJefe2.setCharacterSize(15);
    texOleada.setCharacterSize(10);


    // Cargar efectos de sonido
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

    Bonus.loadFromFile("bonus.wav");
    soundbonus.setBuffer(Bonus);

    tiroRecibido.setVolume(7);
    shoot.setVolume(10);
    tiroRecibidoJefe.setVolume(10);
    explosionColi.setVolume(10);

    // Inicialización de variables de estado
    bandera_oleada = true;

    banderaBonus = false;




    // Temporizador para controlar la aparición de enemigos
    //timerAparicion.restart();

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


    if (menui.getNombreJugador()==""){
        menui.capturarNombreJugador();
        timerAparicion.restart();
    }



        // Verificar tiempo transcurrido y actualizar bandera para aparición de enemigos
        tiempo_transcurrido = timerAparicion.getElapsedTime();
        if (secondLevel == false){
        tiempoRestante = tiempoOleada - tiempo_transcurrido.asSeconds ();
        }
        else{
        tiempoRestante = tiempoOleada2 - tiempo_transcurrido.asSeconds();
        }
        if (secondLevel == false && tiempo_transcurrido.asSeconds() > tiempoOleada)
         {

            bandera_oleada = false;
        }
        else if (tiempo_transcurrido.asSeconds() > tiempoOleada2) {
                bandera_oleada = false;
            }


        // APARICIÓN DE JEFE
        // DISPARO INTERMITENTE CON EL ESPACIO
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (tiempoUltimoDisparo >= intervaloDisparo) {
                niatsu.disparar();
                tiempoUltimoDisparo = 0.0f;
                shoot.play();
            }
        }

        tiempoUltimoDisparo += 1.0 / 60.0;

        // COLISIONES VS PRIMER JEFE
        for (auto& disparo : niatsu.getDisparos()) {
            if (disparo.isCollision(jefe1) && banderaGolpeJefe == false && jefe1.getbandera_jefe_muerto() == false) {
                banderaGolpeJefe = true;
                jefe1.recibedanio();
            }
        }

        for (auto& disparo_primer_jefe : jefe1.getDisparos()) {
            if (disparo_primer_jefe.isCollision(niatsu) && banderaGolpe == false && jefe1.getbandera_jefe_muerto() == false) {
                banderaGolpe = true;
                niatsu.setVida_nave(niatsu.getVida_nave() - 3);
                tiroRecibidoJefe.play();
            }
        }


        // COLISIONES VS SEGUNDO JEFE

        for (auto& disparo : niatsu.getDisparos()) {
            if (disparo.isCollision(jefe2) && banderaGolpeJefe == false && jefe2.getbandera_jefe_muerto2() == false) {
                banderaGolpeJefe = true;
                jefe2.recibedanio();
            }
        }

        for (auto& disparo_segundo_jefe : jefe2.getDisparos()) {
            if (disparo_segundo_jefe.isCollision(niatsu) && banderaGolpe == false && jefe2.getbandera_jefe_muerto2() == false) {
                banderaGolpe = true;
                niatsu.setVida_nave(niatsu.getVida_nave() - 3);
                tiroRecibidoJefe.play();
            }
        }







        // FIN DE COLISIONES PRIMER JEFE

        // MENÚ INTERMEDIO ENTRE MUERTE DE PRIMER JEFE
        if (jefe1.getbandera_jefe_muerto() == true) {

            if (secondLevel == false){
            menui.mostrarMenuPrincipal();
            int opcion = menui.getOpcionSeleccionada();
            if (opcion == 0) {
                timerAparicion.restart();
                bandera_oleada = true;
            for(auto& coli: colis){
                coli.setVida_coli(2);

            }
                secondLevel = true;

                // Continuar juego
            } else if (opcion == 1) {
                window.close(); // Cerrar el juego
            }
         }
        }

        // Actualizar colisiones de disparos con enemigos si bandera_oleada es verdadera
        for (auto& disparo : niatsu.getDisparos()) {
            for (auto& coli : colis) {
                if (disparo.isCollision(coli)) {
                    coli.setVida_coli(coli.getVida() - 1);
                    if (coli.getVida() == 0) {
                        puntos += 100;
                        // Probabilidad del 10% de que aparezca el bonus cuando el coli es destruido
                        if (std::rand() % 10 == 0) {
                            banderaBonus = true;
                            powerup.respawn();
                        }
                    }
                    explosionColi.play();
                }
            }
        }

        if (niatsu.isCollision(powerup)&& banderaBonus == true ) {
            niatsu.setVida_nave(niatsu.getVida_nave() + 1);
            banderaBonus = false;
            powerup.respawn();
            soundbonus.play();
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



        // SEGUNDO NIVEL
        if (secondLevel == true) {
         fondo.cambiarFondo(secondLevel);
         fondo.update(1.0 / 60.0f);

        }

        // INICIO DE UPDATES
        niatsu.update();
        powerup.update();

        if (bandera_oleada == true) {
            fondo.update(1.0 / 60.0f); // Actualiza el fondo con deltaTime
        }

        if (bandera_oleada == true) {
            for (auto& coli : colis) {
                coli.update();
            }
        }

        if (bandera_oleada == false && jefe1.getbandera_jefe_muerto() == false) {
            jefe1.update();
        }
           if (bandera_oleada == false && secondLevel==true) {
            jefe2.update();
        }

        // INICIO DE WINDOWSSSS
        window.clear();

        fondo.draw(window); // Renderiza el fondo

        texPuntos.setPosition({ 800 - texPuntos.getGlobalBounds().width, 0 });
        texVidaJefe1.setPosition({ 400 - texVidaJefe1.getGlobalBounds().width / 2, 0 });
        texOleada.setPosition({ 400 - texOleada.getGlobalBounds().width / 2, 0 });
        texVidaJefe2.setPosition({400 - texVidaJefe2.getGlobalBounds().width /2,0 });

        texPuntos.setString("PUNTOS: " + std::to_string(puntos));
        texvidas.setString("VIDAS: " + std::to_string(niatsu.getVida_nave()));
        texVidaJefe1.setString("VIDAS JEFE: " + std::to_string(jefe1.getVida()));
        texVidaJefe2.setString("VIDAS JEFE: " + std::to_string(jefe2.getVida()));
        texOleada.setString("TIEMPO OLEADA: " + std::to_string(tiempoRestante+1) + " segundos");



        if (bandera_oleada == false && jefe1.getbandera_jefe_muerto() == false) {
            window.draw(texVidaJefe1);
        }
        else if (tiempoRestante > -1)  {
            window.draw(texOleada);
            }
        else if(bandera_oleada == false && jefe2.getbandera_jefe_muerto2() == false && secondLevel == true){
            window.draw(texVidaJefe2);
        }



        window.draw(texvidas);
        window.draw(texPuntos);

        if (banderaBonus == true){
            window.draw(powerup);
        }

        for (auto& disparo : niatsu.getDisparos()) {
            disparo.draw(window, sf::RenderStates::Default);
        }

        if (bandera_oleada == true) {
            for (auto& coli : colis) {
                for (auto& Disparo_enemigo : coli.getDisparos()) {
                    Disparo_enemigo.draw(window, sf::RenderStates::Default);
                }
            }
        }

        if (bandera_oleada == true) {
            for (const auto& coli : colis) {
                window.draw(coli);
            }
        }

        if (bandera_oleada == false && jefe1.getVida() > 0) {
            for (auto& disparo : jefe1.getDisparos()) {
                disparo.draw(window, sf::RenderStates::Default);
            }
        }

        if (bandera_oleada == false && secondLevel== true && jefe2.getbandera_jefe_muerto2() == false) {
            for (auto& disparo : jefe2.getDisparos()) {
                disparo.draw(window, sf::RenderStates::Default);
            }
        }

        if (bandera_oleada == false && secondLevel == false) {
            window.draw(jefe1);
        }


        if (secondLevel == true){
            for(auto& coli : colis){
            coli.coli2donivel();
            }

            for (auto& coli : colis) {
                for (auto& Disparo_enemigo : coli.getDisparos()) {
                    Disparo_enemigo.disparo2do();
                }
            }

        if (bandera_oleada == false && secondLevel == true && jefe2.getbandera_jefe_muerto2() == false) {
            window.draw(jefe2);
        }

        }


        window.draw(niatsu);
        window.display();
    }

if (jefe2.getbandera_jefe_muerto2() == true) {
    // Crear un objeto Jugador con los datos del jugador final
    Jugador jugadorFinal(menui.getNombreJugador(), puntos);

    // Crear o usar un objeto ArchivoJugadores para guardar el registro
    ArchivoJugadores archivoJugadores("jugadores.dat");

    // Llamar a grabarRegistro para guardar los datos del jugador
    if (archivoJugadores.grabarRegistro(jugadorFinal)) {
        std::cout << "Registro de jugador guardado exitosamente." << std::endl;
    } else {
        std::cout << "Error al guardar el registro del jugador." << std::endl;
    }

    // Llamar a listarRegistros para mostrar todos los registros en el archivo
    std::cout << "Listado de todos los registros guardados:" << std::endl;
    archivoJugadores.listarRegistros();
}




}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dibujar elementos adicionales si es necesario
}


