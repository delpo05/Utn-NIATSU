#include "Ranking.h"
#include <iostream>
#include <cstring>
using namespace std;

// Constructor para inicializar el nombre del archivo
ArchivoRanking::ArchivoRanking(const char *n) {
    strcpy(nombreArchivo, n);
}

bool ArchivoRanking::grabarRegistro(const Jugador& jugador) {
    FILE *pArchivo = fopen(nombreArchivo, "ab");
    if (pArchivo == NULL) return false;
    bool exito = fwrite(&jugador, sizeof(Jugador), 1, pArchivo);
    fclose(pArchivo);
    return exito;
}

bool ArchivoRanking::listarRegistros() {
    Jugador jugador;
    FILE *pArchivo = fopen(nombreArchivo, "rb");
    if (pArchivo == NULL) return false;
    while (fread(&jugador, sizeof(Jugador), 1, pArchivo) == 1) {
        jugador.mostrar();
    }
    fclose(pArchivo);
    return true;
}

/*int ArchivoRanking::buscarJugador(const char* nombreBuscado) {
    Jugador jugador;
    FILE *pArchivo = fopen(nombreArchivo, "rb");
    if (pArchivo == NULL) return -2;
    int pos = 0;
    while (fread(&jugador, sizeof(Jugador), 1, pArchivo) == 1) {
        if (strcmp(jugador.getNombre(), nombreBuscado) == 0) {
            fclose(pArchivo);
            return pos;
        }
        pos++;
    }
    fclose(pArchivo);
    return -1;
}*/

Jugador ArchivoRanking::leerRegistro(int posReg) {
    Jugador jugador;
    FILE *pArchivo = fopen(nombreArchivo, "rb");
    if (pArchivo == NULL) return jugador;
    fseek(pArchivo, posReg * sizeof(Jugador), SEEK_SET);
    fread(&jugador, sizeof(Jugador), 1, pArchivo);
    fclose(pArchivo);
    return jugador;
}

int ArchivoRanking::contarRegistros() {
    FILE *pArchivo = fopen(nombreArchivo, "rb");
    if (pArchivo == NULL) return -1;
    fseek(pArchivo, 0, SEEK_END);
    int cantidad = ftell(pArchivo) / sizeof(Jugador);
    fclose(pArchivo);
    return cantidad;
}
