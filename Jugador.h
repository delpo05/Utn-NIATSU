// Jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    std::string nombre;
    int puntos;

public:
    // Constructor por defecto
    Jugador();

    // Constructor con parámetros
    Jugador(const std::string& nombre, int puntos);

    // Setters
    void setNombre(const std::string& nombre);
    void setPuntos(int puntos);

    // Getters
    std::string getNombre() const;
    int getPuntos() const;
};

#endif // JUGADOR_H
