#ifndef ARCHIVO_JUGADORES_H_INCLUDED
#define ARCHIVO_JUGADORES_H_INCLUDED

#include <iostream>
#include <cstring>
#include <cstdio>
#include "Jugador.h"

class ArchivoJugadores {
private:
    char nombreArchivo[50];

public:
    // Constructor por defecto que asigna un nombre de archivo
    ArchivoJugadores(const char* n = "jugadores.dat") {
        std::strcpy(nombreArchivo, n);
    }

    // Funci�n para grabar un registro de jugador en el archivo
    bool grabarRegistro(const Jugador& jugador) {
        FILE* pArchivo = std::fopen(nombreArchivo, "ab");
        if (pArchivo == nullptr) return false;

        int escribio = fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
        std::fclose(pArchivo);
        return escribio == 1;
    }

    // Funci�n para listar todos los registros en el archivo
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

    // Funci�n para contar la cantidad de registros
    int contarRegistros() {
        FILE* pArchivo = std::fopen(nombreArchivo, "rb");
        if (pArchivo == nullptr) return -1;

        fseek(pArchivo, 0, SEEK_END);
        int cantidadRegistros = ftell(pArchivo) / sizeof(Jugador);
        std::fclose(pArchivo);

        return cantidadRegistros;
    }
};

#endif // ARCHIVO_JUGADORES_H_INCLUDED
