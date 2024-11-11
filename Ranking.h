#ifndef ARCHIVO_RANKING_H_INCLUDED
#define ARCHIVO_RANKING_H_INCLUDED

#include "Jugador.h"
#include <cstdio>

class ArchivoRanking {
private:
    char nombreArchivo[50];

public:
    // Constructor para inicializar el nombre del archivo
    ArchivoRanking(const char *n = "rankings.dat");

    // Métodos para gestionar el archivo de rankings
    bool grabarRegistro(const Jugador& jugador);
    bool listarRegistros();
    int buscarJugador(const char* nombreBuscado);
    Jugador leerRegistro(int posReg);
    int contarRegistros();
};

#endif // ARCHIVO_RANKING_H_INCLUDED
