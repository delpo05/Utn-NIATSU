// Menu.cpp

#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window){
    font.loadFromFile("Letra.ttf");  // Cargar la fuente
    opcionSeleccionada = 0;          // Configurar las opciones del menú
    inicializarOpciones();
    texturaFondoMenu.loadFromFile("fondomenu.jpg");
    spriteFondoMenu.setTexture(texturaFondoMenu);

}


void Menu::inicializarOpciones() {
    std::vector<std::string> opciones = {"INICIAR JUEGO", "RANKING", "SALIR"};
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(opciones[i]);
        text.setCharacterSize(30);
        text.setPosition(400 - text.getGlobalBounds().width / 2, 200 + i * 100);
        ///text.setFillColor(i == opcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
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
                    return;  // Salir del menú cuando se presiona Enter
                }
            }
        }
        draw();
    }
}

void Menu::draw() {
    window.clear();
    window.draw(spriteFondoMenu);
    for (size_t i = 0; i < opcionesMenu.size(); ++i) {
        opcionesMenu[i].setFillColor(i == opcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
        window.draw(opcionesMenu[i]);
    }
    window.display();
}

size_t Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}


