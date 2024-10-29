#include <SFML/Graphics.hpp>
#include "Nave.h"
#include "Colis.h"
#include "disparo.h"
#include <SFML/Audio.hpp>


class Game : public sf::Drawable
{
    Nave niatsu;   // Instancia de la nave
    Colis coli1, coli2, coli3;
    sf::RenderWindow window; // Ventana del juego
    sf::Sprite fondo;       // Fondo del juego
    sf::Texture tex;         // Textura del fondo
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

    sf::Sound tiro;
    sf::SoundBuffer audiotiro;



public:
    Game();  // Constructor
    void inicializacion_ventana();   // Inicializa la ventana y elementos
    void iniciar_partida();          // Ciclo principal del juego
    void pausar_partida();           // Pausar el juego (por implementar)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // Dibuja en pantalla
};
