// Menu.h

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    // Constructor que toma la ventana y configura las opciones del menú
    Menu(sf::RenderWindow& window);

    // Métodos para mostrar el menú principal y manejar opciones
    void mostrarMenuPrincipal();
    size_t getOpcionSeleccionada() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture texturaFondoMenu;
    sf::Sprite spriteFondoMenu;
    float velocidad;
    float posicionY;
    std::vector<sf::Text> opcionesMenu;
    size_t opcionSeleccionada;

    // Métodos para inicializar y dibujar las opciones del menú
    void inicializarOpciones();
    void draw();
};
