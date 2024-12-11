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
    ArchivoJugadores(const char* n = "jugadores.dat") {
        std::strcpy(nombreArchivo, n);
    }

bool grabarRegistro(Jugador jugador) {
    Jugador jugadorExistente;
    FILE* pArchivo = fopen(nombreArchivo, "r+b");///lectura/escritura
    if (!pArchivo) {
        pArchivo = fopen(nombreArchivo, "wb");
        if (!pArchivo) return false;
        fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
        fclose(pArchivo);
        return true;
    }


    while (fread(&jugadorExistente, sizeof(Jugador), 1, pArchivo) == 1) {
        if (strcmp(jugador.getNombre(), jugadorExistente.getNombre()) == 0) {
            if (jugador.getPuntos() > jugadorExistente.getPuntos()) {
                fseek(pArchivo, -static_cast<long>(sizeof(Jugador)), SEEK_CUR);
                fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
            }
            fclose(pArchivo);
            return true;
        }
    }

    fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
    fclose(pArchivo);
    return true;
}





    void ordenarVector(std::vector<Jugador>& jugadores) {
        for (size_t i = 0; i < jugadores.size() - 1; i++) {
            for (size_t  j = 0; j < jugadores.size() - i - 1; j++) {
                if (jugadores[j].getPuntos() < jugadores[j + 1].getPuntos()) {
                    Jugador temp = jugadores[j];
                    jugadores[j] = jugadores[j + 1];
                    jugadores[j + 1] = temp;
                }
            }
        }
    }



    std::vector<Jugador> obtenerJugadoresOrdenados() {
        std::vector<Jugador> jugadores;
        Jugador jugador;
        FILE* pArchivo = fopen(nombreArchivo, "rb");

        if (pArchivo == nullptr) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return jugadores;
        }

        while (fread(&jugador, sizeof(Jugador), 1, pArchivo) == 1) {
            jugadores.push_back(jugador);
        }
        fclose(pArchivo);
        ordenarVector(jugadores);

        return jugadores;
    }


  void mostrarRankingSFML(sf::RenderWindow& window) {
    std::vector<Jugador> jugadores = obtenerJugadoresOrdenados();
    sf::Font font;
    font.loadFromFile("Letra.ttf");

    std::vector<sf::Text> textoRanking;

    if (jugadores.empty()) {
        sf::Text noJugadoresText;
        noJugadoresText.setFont(font);
        noJugadoresText.setCharacterSize(15);
        noJugadoresText.setFillColor(sf::Color::White);
        noJugadoresText.setString("POR EL MOMENTO NO HAY GANADORES, SE EL PRIMERO");
        noJugadoresText.setPosition(50, 25);
        textoRanking.push_back(noJugadoresText);
    } else {
        for (size_t i = 0; i < jugadores.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);

            text.setString(std::to_string(i + 1) + ". " + jugadores[i].getNombre() + " - Puntos: " + std::to_string(jugadores[i].getPuntos()));
            text.setPosition(100, 25 + i * 30);
            textoRanking.push_back(text);
        }
    }


    bool esperandoTecla = true;
    while (window.isOpen() && esperandoTecla) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }


            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Escape) {
                    esperandoTecla = false;
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
