#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MenuIntermedio {
public:
    MenuIntermedio(sf::RenderWindow& window);
    void mostrarMenuPrincipal();
    void draw();
    int getOpcionSeleccionada(){return opcionSeleccionada;}
    char* getNombreJugador() { return nombreJugador; }
    void capturarNombreJugador();

private:
    void inicializarOpciones();
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    size_t opcionSeleccionada;

    sf::Text nombreText;  // Texto para mostrar el nombre ingresado
    char nombreJugador[50];  // Array de char para almacenar el nombre
    bool ingresarNombre;  // Bandera para determinar si se está ingresando el nombre
};
