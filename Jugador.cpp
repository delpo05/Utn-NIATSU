#include "Jugador.h"

// Constructor para inicializar los datos del jugador
Jugador::Jugador(std::string n, int p) : nombre(n), puntos(p) {}

// Métodos para establecer y obtener el nombre y los puntos
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

// Método para mostrar los datos del jugador
void Jugador::mostrar() const {
    std::cout << "Nombre: " << nombre << ", Puntos: " << puntos << std::endl;
}

