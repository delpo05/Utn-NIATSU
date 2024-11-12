#include "Jugador.h"

// Constructor para inicializar los datos del jugador
Jugador::Jugador(std::string n, int p) : nombre(n), puntos(p) {}

// M�todos para establecer y obtener el nombre y los puntos
void Jugador::setNombre(const std::string& n) {
    nombre = n;
}

void Jugador::setPuntos(int p) {
    puntos = p;
}

std::string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntos() const {
    return puntos;
}

// M�todo para mostrar los datos del jugador
void Jugador::mostrar() const {
    std::cout << "Nombre: " << nombre << ", Puntos: " << puntos << std::endl;
}

