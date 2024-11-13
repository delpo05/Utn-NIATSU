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
    nombreText.setPosition(10, 0);  // Ajusta la posición según sea necesario

    nombreJugador = "";  // Inicializa el nombre como una cadena vacía
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
    nombreText.setString("Ingrese su nombre: ");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Capturar la entrada de texto para el nombre
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !nombreJugador.empty()) {  // Retroceso
                    nombreJugador.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != '\b') {  // Solo caracteres ASCII
                    nombreJugador += static_cast<char>(event.text.unicode);
                }
                nombreText.setString("Nombre: " + nombreJugador);  // Actualiza el texto en pantalla
            }

            // Si el usuario presiona Enter, termina la entrada del nombre
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return;  // Salir del método una vez ingresado el nombre
            }
        }

        // Dibujar la pantalla de entrada de nombre
        window.clear();
        window.draw(spriteFondoMenu);
        window.draw(nombreText);  // Mostrar el nombre que se va ingresando
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

            // Controles de navegación del menú
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

// Método para obtener el nombre del jugador desde fuera de la clase
std::string MenuIntermedio::getNombreJugador() const {
    return nombreJugador;
}

size_t MenuIntermedio::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}

