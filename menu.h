#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void mostrarMenuPrincipal();
    void draw();
    size_t getOpcionSeleccionada() const;
    std::string getNombreJugador() const;
    void Nombre();
    void inicializarOpciones();

private:
    sf::RenderWindow& ventana;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    size_t opcionSeleccionada;

    sf::Text nombreText;
    std::string nombreJugador;
    bool ingresarNombre = true;
};
