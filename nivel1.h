#ifndef NIVEL1_H
#define NIVEL1_H

#include "Nave.h"
#include "Fondo.h"
#include "primer_jefe.h"
#include "disparo.h"
#include "Colis.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Nivel1 {
public:
    // Constructor
    Nivel1();

    // Métodos de actualización
    void update();
    void handleCollisions();
    void handleDisparos();
    void render();
    bool bandera_jefe_muerto;

private:
    // Objetos gestionados por el nivel
    sf::RenderWindow window;
    Nave niatsu;
    Fondo fondo;
    primer_jefe jefe1;


    std::vector<Colis> colis; // Lista de enemigos (colección de colisiones)

    // Temporizadores y banderas
    sf::Clock timerAparicion;
    float tiempoDeGracia, tiempoDeGracia2, tiempoDeGracia3;
    bool banderaGolpe, banderaGolpeJefe, bandera_oleada;
    bool bandeChoque;
    float tiempoUltimoDisparo, intervaloDisparo;

    // Fuentes y texto
    sf::Font Letra;
    sf::Text texPuntos, texvidas, texVidaJefe1;

    // Sonidos
    sf::SoundBuffer audiochoque, audioshoot, audioRecibetiro, bufferExplosionColi, bufferTiroRecibidoJefe;
    sf::Sound choque, shoot, tiroRecibido, explosionColi, tiroRecibidoJefe;
    int puntos;
};

#endif // NIVEL1_H
