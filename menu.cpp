// Menu.cpp

#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window), opcionSeleccionada(0) {
    // Cargar fuente
    font.loadFromFile("Letra.ttf");
    inicializarOpciones();
}

void Menu::inicializarOpciones() {
    std::vector<std::string> opciones = {"Iniciar Partida", "Opciones", "Salir"};
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(opciones[i]);
        text.setCharacterSize(30);
        text.setPosition(400 - text.getGlobalBounds().width / 2, 200 + i * 50);
        text.setFillColor(i == opcionSeleccionada ? sf::Color::Red : sf::Color::White);
        opcionesMenu.push_back(text);
    }
}

void Menu::mostrarMenuPrincipal() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    opcionSeleccionada = (opcionSeleccionada > 0) ? opcionSeleccionada - 1 : opcionesMenu.size() - 1;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    opcionSeleccionada = (opcionSeleccionada < opcionesMenu.size() - 1) ? opcionSeleccionada + 1 : 0;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    return;
                }
            }
        }
        dibujar();
    }
}

void Menu::dibujar() {
    window.clear();
    for (size_t i = 0; i < opcionesMenu.size(); ++i) {
        opcionesMenu[i].setFillColor(i == opcionSeleccionada ? sf::Color::Red : sf::Color::White);
        window.draw(opcionesMenu[i]);
    }
    window.display();
}

int Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}
