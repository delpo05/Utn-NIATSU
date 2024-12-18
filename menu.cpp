#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : ventana(window) {
    font.loadFromFile("Letra.ttf");
    inicializarOpciones();
    texturaFondoMenu.loadFromFile("fondomenu.jpg");
    spriteFondoMenu.setTexture(texturaFondoMenu);
    opcionSeleccionada = 0;
    ingresarNombre=true;
    nombreText.setFont(font);
    nombreText.setCharacterSize(24);
    nombreText.setFillColor(sf::Color::Yellow);
    nombreText.setPosition(10,0);
}

void Menu::inicializarOpciones() {
    std::vector<std::string> opciones = {"INICIAR JUEGO", "RANKING", "SALIR"};
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(opciones[i]);
        text.setCharacterSize(30);
        text.setPosition(400 - text.getGlobalBounds().width / 2, 200 + i * 100);
        opcionesMenu.push_back(text);

    }
}

void Menu::mostrarMenuPrincipal() {
    while (ventana.isOpen()) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
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
        draw();
    }
}

void Menu::draw() {
    ventana.clear();
    ventana.draw(spriteFondoMenu);


        for (size_t i = 0; i < opcionesMenu.size(); ++i) {
            opcionesMenu[i].setFillColor(i == opcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
            ventana.draw(opcionesMenu[i]);
        }


    ventana.display();
}

size_t Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}

std::string Menu::getNombreJugador() const {
    return nombreJugador;
}

