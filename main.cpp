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

    while (window.isOpen()) {
        menu.mostrarMenuPrincipal();

        int opcion = menu.getOpcionSeleccionada();

        if (opcion == 0) {
            Game game;
        } else if (opcion == 1) {
            ArchivoJugadores archivoJugadores("Jugadores.dat");
            archivoJugadores.mostrarRankingSFML(window);
        } else if (opcion == 2) {
            window.close();
            break;
        }
    }

    return 0;
}

