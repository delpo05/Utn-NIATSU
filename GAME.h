// game.h
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Colis.h"
#include "disparo.h"
#include "fondo.h"
#include "primer_jefe.h"
#include <SFML/Audio.hpp>
#include <vector>
#include "menuIntermedio.h"



class Game : public sf::Drawable {
    Nave niatsu;   // Instancia de la nave
    primer_jefe jefe1;
    std::vector<Colis> colis;  // Vector para almacenar enemigos
     // Ventana del juego
    //sf::Sprite fondo;       // Fondo del juego
    sf::Texture tex;        // Textura del fondo
    sf::Music Musica;
    sf::Font Letra;
    sf::Text texvidas;
    sf::Text texPuntos;
    sf::Text texVidaJefe1;
    sf::Text texOleada;


    bool banderaGolpe = false;
    bool bandeChoque = false;
    bool banderaGolpeJefe = false;
    sf::RenderWindow window;
    sf::RenderWindow windowIntermedio;
    int tiempoDeGracia;
    int tiempoDeGracia2;
    int tiempoDeGracia3;
    float tiempoUltimoDisparo;
    float intervaloDisparo;
    int puntos;
    sf::Sound choque;
    sf::SoundBuffer audiochoque;
    sf::Sound shoot;
    sf::SoundBuffer audioshoot;
    sf::Sound tiroRecibido;
    sf::SoundBuffer audioRecibetiro;
    sf::Sound explosionColi;
    sf::SoundBuffer bufferExplosionColi;
    sf::Sound tiroRecibidoJefe;
    sf::SoundBuffer bufferTiroRecibidoJefe;
    sf::Clock timerAparicion;
    sf::Time tiempo_transcurrido;
    bool bandera_oleada;
    int movimiento_de_fondo;
    Fondo fondo;
    bool secondLevel = false;
    int tiempoRestante;
    int tiempoOleada;
    int tiempoOleada2;



public:
    Game();  // Constructor

    void inicializacion_ventana();   // Inicializa la ventana y elementos
    void iniciar_partida();          // Ciclo principal del juego
    void pausar_partida();           // Pausar el juego (por implementar)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // Dibuja en pantalla
};

