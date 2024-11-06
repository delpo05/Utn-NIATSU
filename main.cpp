#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>
#include "GAME.h"
#include "menu.h"


int main()
{
sf::RenderWindow window(sf::VideoMode(800, 600), "NIATSU - Menu");

    // Crear e iniciar el menú
    Menu menu(window);
    menu.mostrarMenuPrincipal();

    // Verificar la opción seleccionada
    int opcion = menu.getOpcionSeleccionada();
    if (opcion == 0) {
        Game game;    // Inicia el juego si se selecciona "Iniciar juego"
    } else if (opcion == 1) {
        // Mostrar el ranking (puedes implementar esta sección para mostrar un ranking)
    } else if (opcion == 2) {
        window.close();   // Cierra la ventana si se selecciona "Salir"
    }


return 0;
}
