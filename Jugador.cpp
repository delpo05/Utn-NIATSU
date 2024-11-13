#include "Jugador.h"
#include <cstring> // Para usar strncpy

// Constructor por defecto
Jugador::Jugador() {
    std::strncpy(nombre, "", sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
    puntos = 0;
}

// Constructor con parámetros
Jugador::Jugador(const char* nombre, int puntos) {
    std::strncpy(this->nombre, nombre, sizeof(this->nombre) - 1);
    this->nombre[sizeof(this->nombre) - 1] = '\0';
    this->puntos = puntos;
}

// Setters
void Jugador::setNombre(const char* nombre) {
    std::strncpy(this->nombre, nombre, sizeof(this->nombre) - 1);
    this->nombre[sizeof(this->nombre) - 1] = '\0';
}

void Jugador::setPuntos(int puntos) {
    this->puntos = puntos;
}

// Getters
const char* Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntos() const {
    return puntos;
}

