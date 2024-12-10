#include "Jugador.h"
#include <cstring> // Para usar strncpy


Jugador::Jugador() {
    std::strncpy(nombre, "", sizeof(nombre) - 1);
    puntos = 0;
}


Jugador::Jugador(char* n, int p) {
    std::strncpy(nombre, n, sizeof(nombre));
    puntos = p;
}


const char* Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntos() const {
    return puntos;
}
