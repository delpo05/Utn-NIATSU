#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "GAME.h"
#include "menu.h"
#include <iostream>

using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "NIATSU - Menu");
    Menu menu(window);
    menu.mostrarMenuPrincipal();



    int opcion = menu.getOpcionSeleccionada();
    if (opcion == 0) {
        Game game;
        game.setNombre(menu.getNombreJugador());

        // Puedes pasar `nombreJugador` a la clase `Game` si deseas usarlo dentro del juego
    } else if (opcion == 1) {
        // Mostrar el ranking
    } else if (opcion == 2) {
        window.close();
    }

    return 0;
}
