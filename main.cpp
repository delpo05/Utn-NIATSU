#include "Nave.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <stdlib.h>


int main()
{
/// COMENTARIO DE PRUEba prueba
    /// Inicializacion de la ventanta
    sf::RenderWindow window(sf::VideoMode(800, 600), "NIATSU");
    window.setFramerateLimit(60);


    Nave nave;


    sf::Sprite imagen;
    sf::Texture tex;
    tex.loadFromFile("fondo espacio.jpg");

    imagen.setTexture(tex);


    ///GAME LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



    /// COLA DE MENSAJES (EJECUTO LOS COMANDOS



    /// UPDATE - ACTUALIZA LOS ESTADOS DEL JUEGO
        nave.update();


        window.clear();

    /// DRAW
        window.draw(imagen);
        window.draw(nave);


       // window.draw(Nave);




        window.display();
    }

    return 0;
}
