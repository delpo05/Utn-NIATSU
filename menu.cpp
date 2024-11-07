#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("Letra.ttf");
    inicializarOpciones();
    texturaFondoMenu.loadFromFile("fondomenu.jpg");
    spriteFondoMenu.setTexture(texturaFondoMenu);
    opcionSeleccionada = 0;
    ingresarNombre=true;

    // Inicializar el texto para mostrar el nombre ingresado
    nombreText.setFont(font);
    nombreText.setCharacterSize(24);
    nombreText.setFillColor(sf::Color::Yellow);
    nombreText.setPosition(10,0);  // Ajusta la posición según sea necesario
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
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Manejador para ingresar el nombre del jugador
            if (ingresarNombre == true) {

                nombreText.setString("Nombre de usuario: " + nombreJugador);
                if (event.type == sf::Event::TextEntered) {

                    if (event.text.unicode == '\b' && !nombreJugador.empty()) { // Borrar con retroceso
                        nombreJugador.pop_back();
                    } else if (event.text.unicode < 128 && event.text.unicode != '\b') { // Solo caracteres ASCII
                        nombreJugador += static_cast<char>(event.text.unicode);
                    }

                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    ingresarNombre = false; // Finalizar ingreso de nombre
                }
                //FIN DE INGRESO DE NOMBRE
            } else {
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
        }
        draw();
    }
}

void Menu::draw() {
    window.clear();
    window.draw(spriteFondoMenu);

    if (ingresarNombre) {
        window.draw(nombreText); // Dibujar el campo de texto para el nombre
    } else {
        for (size_t i = 0; i < opcionesMenu.size(); ++i) {
            opcionesMenu[i].setFillColor(i == opcionSeleccionada ? sf::Color::Yellow : sf::Color::White);
            window.draw(opcionesMenu[i]);
        }
    }

    window.display();
}

size_t Menu::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}

std::string Menu::getNombreJugador() const {
    return nombreJugador;
}

