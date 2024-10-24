#include <SFML/Graphics.hpp>
#include "Nave.h"

class Game : public sf::Drawable {
    Nave niatsu;             // Instancia de la nave
    sf::RenderWindow window; // Ventana del juego
    sf::Sprite imagen;       // Fondo del juego
    sf::Texture tex;         // Textura del fondo

public:
    Game();  // Constructor
    void inicializacion_ventana();   // Inicializa la ventana y elementos
    void iniciar_partida();          // Ciclo principal del juego
    void update();                   // Actualiza el estado del juego
    void pausar_partida();           // Pausar el juego (por implementar)
    void actualizar_puntuacion();    // Actualizar puntuación (por implementar)
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // Dibuja en pantalla
};
