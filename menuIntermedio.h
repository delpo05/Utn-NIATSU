#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MenuIntermedio {
public:
    MenuIntermedio(sf::RenderWindow& window);
    void mostrarMenuPrincipal();
    void draw();
    size_t getOpcionSeleccionada() const;
    std::string getNombreJugador() const; // Nueva función para obtener el nombre del jugador
    void Nombre();
    void capturarNombreJugador();



private:
    void inicializarOpciones();
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    size_t opcionSeleccionada;

    sf::Text nombreText; // Texto para mostrar el nombre ingresado
    std::string nombreJugador; // String para almacenar el nombre
    bool ingresarNombre; // Bandera para determinar si se está ingresando el nombre
};
