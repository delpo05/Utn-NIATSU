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
        FILE* pArchivo = std::fopen(nombreArchivo, "ab");
        if (pArchivo == nullptr) return false;

        int escribio = fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
        std::fclose(pArchivo);
        return escribio == 1;
    }

    // Función para listar todos los registros en el archivo
    bool listarRegistros() {
        Jugador jugador;
        FILE* pArchivo = std::fopen(nombreArchivo, "rb");
        if (pArchivo == nullptr) return false;

        while (fread(&jugador, sizeof(Jugador), 1, pArchivo) == 1) {
            std::cout << "Nombre: " << jugador.getNombre() << " - Puntos: " << jugador.getPuntos() << std::endl;
        }

        std::fclose(pArchivo);
        return true;
    }

    // Función para contar la cantidad de registros
    int contarRegistros() {
        FILE* pArchivo = std::fopen(nombreArchivo, "rb");
        if (pArchivo == nullptr) return -1;

        fseek(pArchivo, 0, SEEK_END);
        int cantidadRegistros = ftell(pArchivo) / sizeof(Jugador);
        std::fclose(pArchivo);

        return cantidadRegistros;
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
        for (size_t i = 0; i < jugadores.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            // Formatear el texto de cada jugador con posición, nombre y puntos
            text.setString(std::to_string(i + 1) + ". " + jugadores[i].getNombre() +
                           " - Puntos: " + std::to_string(jugadores[i].getPuntos()));
            text.setPosition(100, 100 + i * 30);  // Ajusta la posición vertical de cada jugador
            textoRanking.push_back(text);
        }

        // Mostrar el ranking en la ventana
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                    window.close();  // Cierra la ventana si el usuario presiona 'Escape'
                    return;
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
