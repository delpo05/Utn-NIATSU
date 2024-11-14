#ifndef ARCHIVO_JUGADORES_H_INCLUDED
#define ARCHIVO_JUGADORES_H_INCLUDED

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include "Jugador.h"

class ArchivoJugadores {
private:
    char nombreArchivo[50];

public:
    // Constructor por defecto que asigna un nombre de archivo
    ArchivoJugadores(const char* n = "jugadores.dat") {
        std::strcpy(nombreArchivo, n);
    }

    // Función para grabar un registro de jugador en el archivo
bool grabarRegistro(Jugador jugador) {
    Jugador jugadorExistente;
    FILE* pArchivo = fopen(nombreArchivo, "r+b"); // Abrir el archivo en modo lectura/escritura
    if (!pArchivo) {
        // Si el archivo no existe, lo creamos en modo escritura y guardamos el jugador
        pArchivo = fopen(nombreArchivo, "wb");
        if (!pArchivo) return false;
        fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
        fclose(pArchivo);
        return true;
    }


    while (fread(&jugadorExistente, sizeof(Jugador), 1, pArchivo) == 1) {
        if (strcmp(jugador.getNombre(), jugadorExistente.getNombre()) == 0) {
            // Si se encuentra el jugador y el puntaje es mayor, actualizar el registro
            if (jugador.getPuntos() > jugadorExistente.getPuntos()) {
                fseek(pArchivo, -static_cast<long>(sizeof(Jugador)), SEEK_CUR);
                fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
            }
            fclose(pArchivo);
            return true;
        }
    }

    // Si el jugador no está en el archivo, agregarlo al final
    fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
    fclose(pArchivo);
    return true;
}





    // Ordenar el vector de jugadores por puntos (de mayor a menor)
    void ordenarVector(std::vector<Jugador>& jugadores) {
        for (size_t i = 0; i < jugadores.size() - 1; i++) {
            for (size_t  j = 0; j < jugadores.size() - i - 1; j++) {
                if (jugadores[j].getPuntos() < jugadores[j + 1].getPuntos()) {
                    // Intercambiar los jugadores si están desordenados
                    Jugador temp = jugadores[j];
                    jugadores[j] = jugadores[j + 1];
                    jugadores[j + 1] = temp;
                }
            }
        }
    }



    // Cargar los jugadores desde el archivo, ordenar y devolver el vector
    std::vector<Jugador> obtenerJugadoresOrdenados() {
        std::vector<Jugador> jugadores;
        Jugador jugador;
        FILE* pArchivo = std::fopen(nombreArchivo, "rb");

        if (pArchivo == nullptr) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return jugadores;
        }

        // Cargar jugadores desde el archivo al vector
        while (fread(&jugador, sizeof(Jugador), 1, pArchivo) == 1) {
            jugadores.push_back(jugador);
        }
        fclose(pArchivo);

        // Ordenar los jugadores por puntos de mayor a menor
        ordenarVector(jugadores);

        return jugadores;
    }

    // Mostrar el ranking de jugadores en la ventana de SFML
  void mostrarRankingSFML(sf::RenderWindow& window) {
    // Obtener los jugadores ordenados
    std::vector<Jugador> jugadores = obtenerJugadoresOrdenados();

    // Configurar la fuente y el texto de SFML
    sf::Font font;
    font.loadFromFile("Letra.ttf");

    std::vector<sf::Text> textoRanking;

    // Verificar si no hay jugadores
    if (jugadores.empty()) {
        sf::Text noJugadoresText;
        noJugadoresText.setFont(font);
        noJugadoresText.setCharacterSize(15);
        noJugadoresText.setFillColor(sf::Color::White);
        noJugadoresText.setString("POR EL MOMENTO NO HAY GANADORES, SE EL PRIMERO");
        noJugadoresText.setPosition(50, 25);  // Colocar el texto en una posición central
        textoRanking.push_back(noJugadoresText);
    } else {
        // Si hay jugadores, agregar el ranking
        for (size_t i = 0; i < jugadores.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            // Formatear el texto de cada jugador con posición, nombre y puntos
            text.setString(std::to_string(i + 1) + ". " + jugadores[i].getNombre() +
                           " - Puntos: " + std::to_string(jugadores[i].getPuntos()));
            text.setPosition(100, 25 + i * 30);  // Ajusta la posición vertical de cada jugador
            textoRanking.push_back(text);
        }
    }

    // Mostrar el ranking en la ventana
    bool esperandoTecla = true;  // Variable para controlar la espera de una tecla
    while (window.isOpen() && esperandoTecla) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Cuando se presiona una tecla, se puede salir
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Escape) {
                    esperandoTecla = false;  // Deja de esperar y regresa al menú
                }
            }
        }

        window.clear();
        for (const auto& text : textoRanking) {
            window.draw(text);
        }
        window.display();
    }
}

};

#endif // ARCHIVO_JUGADORES_H_INCLUDED
