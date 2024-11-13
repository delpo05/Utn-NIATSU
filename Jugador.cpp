// Jugador.cpp
#include "Jugador.h"

// Constructor por defecto
Jugador::Jugador() : nombre(""), puntos(0) {}

// Constructor con parámetros
Jugador::Jugador(const std::string& nombre, int puntos) : nombre(nombre), puntos(puntos) {}

// Setters
void Jugador::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Jugador::setPuntos(int puntos) {
    this->puntos = puntos;
}

// Getters
std::string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntos() const {
    return puntos;
}
