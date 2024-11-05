// Menu.h

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    // Constructor que toma la ventana y configura las opciones del menú
    Menu(sf::RenderWindow& window);

    // Métodos para mostrar y manejar el menú principal y el menú de pausa
    void mostrarMenuPrincipal();
    void mostrarMenuPausa();
    int getOpcionSeleccionada() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    int opcionSeleccionada;

    // Métodos para inicializar los textos de las opciones del menú
    void inicializarOpciones();
    void dibujar();
};
