#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "GAME.h"
#include "menu.h"
#include <iostream>
#include "JugadorArchivo.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "NIATSU - Menu");
    Menu menu(window);

    // Bucle principal del menú
    while (window.isOpen()) {
        menu.mostrarMenuPrincipal();

        int opcion = menu.getOpcionSeleccionada();

        if (opcion == 0) {
            // Iniciar el juego
            Game game;
        } else if (opcion == 1) {
            // Mostrar el ranking y esperar a que el usuario presione una tecla
            ArchivoJugadores archivoJugadores("Jugadores.dat");
            archivoJugadores.mostrarRankingSFML(window);
        } else if (opcion == 2) {
            // Salir del juego
            window.close();
            break;
        }
    }

    return 0;
}

