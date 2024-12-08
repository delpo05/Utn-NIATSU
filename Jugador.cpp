#include "Jugador.h"
#include <cstring> // Para usar strncpy

// Constructor por defecto
Jugador::Jugador() {
    std::strncpy(nombre, "", sizeof(nombre) - 1);
    puntos = 0;
}

// Constructor con parámetros
Jugador::Jugador(char* n, int p) {
    std::strncpy(nombre, n, sizeof(nombre));
    //this->nombre[sizeof(this->nombre) - 1] = '\0';
    puntos = p;
}


const char* Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntos() const {
    return puntos;
}
