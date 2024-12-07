#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void mostrarMenuPrincipal();
    void draw();
    size_t getOpcionSeleccionada() const;
    std::string getNombreJugador() const; // Nueva funci�n para obtener el nombre del jugador
    void Nombre();
    void inicializarOpciones();

private:
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    size_t opcionSeleccionada;

    sf::Text nombreText; // Texto para mostrar el nombre ingresado
    std::string nombreJugador; // String para almacenar el nombre
    bool ingresarNombre = true; // Bandera para determinar si se est� ingresando el nombre
};
