// Menu.h

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    // Constructor que toma la ventana y configura las opciones del men�
    Menu(sf::RenderWindow& window);

    // M�todos para mostrar y manejar el men� principal y el men� de pausa
    void mostrarMenuPrincipal();
    void mostrarMenuPausa();
    int getOpcionSeleccionada() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<sf::Text> opcionesMenu;
    int opcionSeleccionada;

    // M�todos para inicializar los textos de las opciones del men�
    void inicializarOpciones();
    void dibujar();
};
