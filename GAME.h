// game.h
#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Colis.h"
#include "disparo.h"
#include <SFML/Audio.hpp>
#include <vector>

class Game : public sf::Drawable {
    Nave niatsu;   // Instancia de la nave
    std::vector<Colis> colis;  // Vector para almacenar enemigos
    sf::RenderWindow window; // Ventana del juego
    sf::Sprite fondo;       // Fondo del juego
    sf::Texture tex;        // Textura del fondo
    sf::Music Musica;
    sf::Font Letra;
    sf::Text texvidas;
    sf::Text texPuntos;

    bool banderaGolpe = false;
    bool bandeChoque = false;
    int tiempoDeGracia;
    float tiempoUltimoDisparo;
    float intervaloDisparo;
    int puntos;
    sf::Sound choque;
    sf::SoundBuffer audiochoque;
    sf::Sound shoot;
    sf::SoundBuffer audioshoot;
    sf::Sound tiroRecibido;
    sf::SoundBuffer audioRecibetiro;
    sf::Clock timerAparicion;
    sf::Time tiempo_transcurrido;
    bool bandera_ejemplo;
    int movimiento_de_fondo;

public:
    Game();  // Constructor
    void inicializacion_ventana();   // Inicializa la ventana y elementos
    void iniciar_partida();          // Ciclo principal del juego
    void pausar_partida();           // Pausar el juego (por implementar)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // Dibuja en pantalla
};

