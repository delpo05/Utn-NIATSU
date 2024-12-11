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
    sf::RenderWindow& ventana;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    size_t opcionSeleccionada;

    sf::Text nombreText;
    char nombreJugador[50];
    bool ingresarNombre;
};
