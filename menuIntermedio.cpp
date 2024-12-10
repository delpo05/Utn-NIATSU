#include "menuIntermedio.h"
#include <cstring>

MenuIntermedio::MenuIntermedio(sf::RenderWindow& window) : window(window), opcionSeleccionada(0), ingresarNombre(true) {
    font.loadFromFile("Letra.ttf");
    inicializarOpciones();
    texturaFondoMenu.loadFromFile("fondomenu.jpg");
    spriteFondoMenu.setTexture(texturaFondoMenu);


    nombreText.setFont(font);
    nombreText.setCharacterSize(24);
    nombreText.setFillColor(sf::Color::Yellow);
    nombreText.setPosition(10, 0);

    memset(nombreJugador, 0, sizeof(nombreJugador));
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

void MenuIntermedio::capturarNombreJugador() {
    int indice = 0;
    nombreText.setString("Ingrese su nombre: ");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && indice > 0) {
                    nombreJugador[--indice] = '\0';
                } else if (event.text.unicode < 128 && event.text.unicode != '\b' && indice < 49) {  // Solo caracteres ASCII y límite de 49 caracteres
                    nombreJugador[indice++] = static_cast<char>(event.text.unicode);
                    nombreJugador[indice] = '\0';  // Mantiene el final nulo de la cadena
                }
                nombreText.setString("Ingrese su nombre: " + std::string(nombreJugador));
            }


            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return;
            }
        }


        window.clear();
        window.draw(spriteFondoMenu);
        window.draw(nombreText);
        window.display();
    }
}

void MenuIntermedio::mostrarMenuPrincipal() {
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

