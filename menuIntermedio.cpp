#include "menuIntermedio.h"

MenuIntermedio::MenuIntermedio(sf::RenderWindow& window) : window(window), opcionSeleccionada(0), ingresarNombre(true) {
    font.loadFromFile("Letra.ttf");
    inicializarOpciones();
    texturaFondoMenu.loadFromFile("fondomenu.jpg");
    spriteFondoMenu.setTexture(texturaFondoMenu);

    // Inicializar el texto para mostrar el nombre ingresado
    nombreText.setFont(font);
    nombreText.setCharacterSize(24);
    nombreText.setFillColor(sf::Color::Yellow);
    nombreText.setPosition(10,0);  // Ajusta la posición según sea necesario
}

void MenuIntermedio::inicializarOpciones() {
    std::vector<std::string> opciones = {"CONTINUAR", "SALIR"};
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(opciones[i]);
        text.setCharacterSize(30);
        text.setPosition(400 - text.getGlobalBounds().width / 2, 200 + i * 100);
        opcionesMenu.push_back(text);

    }
}

void MenuIntermedio::mostrarMenuPrincipal() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Manejador para ingresar el nombre del jugador

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

void MenuIntermedio::draw() {
    window.clear();
    window.draw(spriteFondoMenu);

        for (size_t i = 0; i < opcionesMenu.size(); ++i) {
            opcionesMenu[i].setFillColor(i == opcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
            window.draw(opcionesMenu[i]);
        }


    window.display();
}

size_t MenuIntermedio::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}

